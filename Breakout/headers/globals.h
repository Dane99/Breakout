#pragma once

namespace globals {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const int PADDLE_HEIGHT = 10;
	const int PADDLE_LENGTH = 120;
	const int PADDLE_Y = 430;

	const int BLOCK_HEIGHT = 15;
	const int BLOCK_LENGTH = 60;

	const int NUMBER_HORIZONTAL_BLOCKS = 9;
	const int NUMBER_VERTICAL_BLOCKS = 5;

	const float BALL_SPEED = 1.5f;

	const int BALL_DIAMETER = 18;
}


struct Vector2 {
	int x, y;
	Vector2() :
		x(0), y(0)
	{}

	Vector2(int x, int y) :
		x(x), y(y)
	{}

	Vector2 zero() {
		return Vector2(0, 0);
	}
};