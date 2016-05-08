#pragma once
#include "SDL.h"
#include <string>
#include "block.h"
#include "globals.h"

class Graphics;

class Ball {
public:
	Ball();

	Ball(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
		float posX, float posY);

	void draw(Graphics &graphics);

	void checkGeneralCollisons(float paddleX, float paddleY);

	bool Ball::checkBlockCollison(float bY, float bX);

	void update(float elapsedTime, float paddleX, float paddleY);

	bool isGameOver();
private:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;

	bool _gameOver = false;
	float _x, _y;
	float _velx = 0.2f * globals::BALL_SPEED, _vely = -0.1f * globals::BALL_SPEED;
};