#pragma once
#include "SDL.h"
#include <string>

class Graphics;

class Paddle {
public:
	Paddle();

	Paddle(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
		float posX, float posY);

	void draw(Graphics &graphics);

	void moveLeft();
	void moveRight();

	void stopMoving();

	float getPosX();
	float getPosY();

	void update(float elapsedTime);

private:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;

	float _x, _y;
	float _dx, dy;

};