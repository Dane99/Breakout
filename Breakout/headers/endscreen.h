#pragma once
#include "SDL.h"
#include <string>

class Graphics;

class Endscreen {
public:
	Endscreen();

	Endscreen(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
		float posX, float posY);

	void draw(Graphics &graphics);

private:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;

	float _x, _y;

};