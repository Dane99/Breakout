#pragma once

#include "paddle.h"
#include "block.h"
#include "globals.h"
#include "ball.h"
#include "endscreen.h"

class Graphics;

class Game {
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void drawGameOver(Graphics &graphics);
	void drawWin(Graphics &graphics);
	void update(float elapsedTime);
	bool allBlocksHiden();

	Paddle _paddle;
	Block _block[globals::NUMBER_VERTICAL_BLOCKS][globals::NUMBER_HORIZONTAL_BLOCKS];
	Ball _ball;
	Endscreen _gameover;
	Endscreen _win;
};