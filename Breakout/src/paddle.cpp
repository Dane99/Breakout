#include "../headers/paddle.h"
#include "../headers/graphics.h"
#include "../headers/globals.h"

namespace paddle_constants {
	const float PADDLE_SPEED = 0.4f;
}

Paddle::Paddle()
{
}

Paddle::Paddle(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
	float posX, float posY) :
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

void Paddle::draw(Graphics & graphics)
{
	SDL_Rect destinationRectangle = { this->_x, this->_y, this->_sourceRect.w, this->_sourceRect.h};
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void Paddle::moveLeft()
{
	this->_dx = -paddle_constants::PADDLE_SPEED;
}

void Paddle::moveRight()
{
	this->_dx = paddle_constants::PADDLE_SPEED;
}

void Paddle::stopMoving()
{
	this->_dx = 0;
}

float Paddle::getPosX()
{
	return this->_x;
}

float Paddle::getPosY()
{
	return this->_y;
}

void Paddle::update(float elapsedTime)
{
	if (this->_x < 0) this->_x = 0;
	if (this->_x > globals::SCREEN_WIDTH - globals::PADDLE_LENGTH) this->_x = globals::SCREEN_WIDTH - globals::PADDLE_LENGTH;

	this->_x += this->_dx * elapsedTime;	
	//std::cout << this->_x << std::endl;
}
