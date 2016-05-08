#include "ball.h"
#include "graphics.h"
#include "globals.h"
#include "block.h"

Ball::Ball()
{
}

Ball::Ball(Graphics & graphics, const std::string & filePath, int sourceX, int sourceY, int width, int height, float posX, float posY)
	:
	_x(posX),
	_y(posY)
{
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = width;
	this->_sourceRect.h = height;

	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	if (this->_spriteSheet == NULL) {
		printf("\nError: Unable to load image\n");
	}
}

void Ball::draw(Graphics & graphics)
{
	SDL_Rect destinationRectangle = { this->_x, this->_y, this->_sourceRect.w, this->_sourceRect.h };
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void Ball::checkGeneralCollisons(float paddleX, float paddleY)
{
	if (this->_x < 0) {
		this->_x = 0;
		this->_velx *= -1;
	}
	if (this->_x > globals::SCREEN_WIDTH - globals::BALL_DIAMETER) {
		this->_x = globals::SCREEN_WIDTH - globals::BALL_DIAMETER;
		this->_velx *= -1;
	}
	if (this->_y < 0) {
		this->_y = 0;
		this->_vely *= -1;
	}
	if (this->_y > globals::SCREEN_HEIGHT - globals::BALL_DIAMETER) {
		_gameOver = true;
	}

	if (this->_y + globals::BALL_DIAMETER > globals::PADDLE_Y							  // the +global ball diameter to get the bottom of the ball
		&& this->_y < globals::PADDLE_Y + globals::PADDLE_HEIGHT // the -global ball diameter to get the top of the ball
		&& this->_x + globals::BALL_DIAMETER > paddleX									  // the +global ball diameter to get the right of the ball
		&& this->_x - globals::BALL_DIAMETER < paddleX + globals::PADDLE_LENGTH) {		  // the -global ball diameter to get the left of the ball
		this->_vely *= -1; // TODO make this work for when the ball hits the side of the padddle


	}
	
}

bool Ball::checkBlockCollison(float bX, float bY)
{
	if (this->_y + globals::BALL_DIAMETER > bY
		&& this->_y < bY + globals::BLOCK_HEIGHT
		&& this->_x + globals::BALL_DIAMETER > bX
		&& this->_x - globals::BALL_DIAMETER < bX + globals::BLOCK_LENGTH) {
		this->_vely *= -1;
		this->_y += this->_vely;
		return true;
	}

	return false;
}

void Ball::update(float elapsedTime, float paddleX, float paddleY)
{
	this->checkGeneralCollisons(paddleX, paddleY);
	this->_x += this->_velx * elapsedTime;
	this->_y += this->_vely * elapsedTime;
}

bool Ball::isGameOver()
{
	return this->_gameOver;
}
