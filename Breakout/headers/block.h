#pragma once
#include "SDL.h"
#include <string>

class Graphics;

class Block {
public:
	Block();

	Block(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
		float posX, float posY);

	void draw(Graphics &graphics);

	void update();

	void hide();

	bool isHiden();

	float getX();
	float getY();
protected:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;

	float _x, _y;
	bool _isHiden = false;

};