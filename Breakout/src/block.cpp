#include "block.h"
#include "graphics.h"

Block::Block()
{
}

// posX/posY is where we want to draw.
// width/height is how big it is
// sourceX/sourceY is where we want it
Block::Block(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
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

void Block::draw(Graphics & graphics)
{
	if (!this->_isHiden) {
		SDL_Rect destinationRectangle = { this->_x, this->_y, this->_sourceRect.w, this->_sourceRect.h };
		graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
	}
}

void Block::update()
{
}

void Block::hide()
{
	this->_isHiden = true;
}

bool Block::isHiden()
{
	return this->_isHiden;
}

float Block::getX()
{
	return this->_x;
}

float Block::getY()
{
	return this->_y;
}
