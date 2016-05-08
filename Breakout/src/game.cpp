#include "SDL.h"

#include <algorithm>
#include "globals.h"
#include "game.h"
#include "graphics.h"
#include "input.h"
#include "ball.h"
#include "endscreen.h"
#include <cstdlib> 


/* Game Class
*  This class holds all information for our main game loop.
*/

namespace {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 1000 / FPS;
}

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}
Game::~Game()
{
}

void Game::gameLoop()
{
	Graphics graphics;
	Input input;
	SDL_Event event;
	for (int y = 0; y < globals::NUMBER_VERTICAL_BLOCKS; y++) {
		for (int x = 0; x < globals::NUMBER_HORIZONTAL_BLOCKS; x++) {
			this->_block[y][x] = Block(graphics, "content/block.png", 0, 0, globals::BLOCK_LENGTH, globals::BLOCK_HEIGHT, 10 + 70 * x, 50 + 30*y);
		}
	}
	this->_paddle = Paddle(graphics, "content/paddle.png", 0, 0, globals::PADDLE_LENGTH, globals::PADDLE_HEIGHT, (int)(globals::SCREEN_WIDTH/2-globals::PADDLE_LENGTH/2), globals::PADDLE_Y);
	this->_ball = Ball(graphics, "content/ball.png", 0, 0, globals::BALL_DIAMETER, globals::BALL_DIAMETER, 200, 300);
	this->_gameover = Endscreen(graphics, "content/gameover.png", 0, 0, 640, 480, 0, 0);
	this->_win = Endscreen(graphics, "content/win.png", 0, 0, 640, 480, 0, 0);
	int last_update_time = SDL_GetTicks();
	//Start game loop
	while (true) {
	


		input.beginNewFrame();

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {  // means we have a new key i.e (Not Repeating)
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}

		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}
		else if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true) {
			this->_paddle.moveLeft();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true) {
			this->_paddle.moveRight();
		}

		if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
			this->_paddle.stopMoving();
		}

		const int CURRENT_TIME_MS = SDL_GetTicks(); // const because it us used just for the first run through
		int elapsed_time_ms = CURRENT_TIME_MS - last_update_time;
		last_update_time = CURRENT_TIME_MS;

		if (!this->_ball.isGameOver() && !this->allBlocksHiden()) {
			this->update(std::min(elapsed_time_ms, MAX_FRAME_TIME));
			this->draw(graphics);
		}

		if (this->_ball.isGameOver()) {
			this->drawGameOver(graphics);
			system("PAUSE");  // temp workaround
			return;
		}
		if (this->allBlocksHiden()) {
			this->drawWin(graphics);
			system("PAUSE"); // temp workaround
			return;
		}

	}
}

void Game::draw(Graphics &graphics)
{
	graphics.clear();

	for (int y = 0; y < globals::NUMBER_VERTICAL_BLOCKS; y++) {
		for (int x = 0; x < globals::NUMBER_HORIZONTAL_BLOCKS; x++) {
			this->_block[y][x].draw(graphics);
		}
	}
	this->_paddle.draw(graphics);
	this->_ball.draw(graphics);
	graphics.flip();

}

void Game::drawGameOver(Graphics &graphics)
{
	graphics.clear();
	this->_gameover.draw(graphics);
	graphics.flip();
}

void Game::drawWin(Graphics &graphics)
{
	graphics.clear();
	this->_win.draw(graphics);
	graphics.flip();
}

void Game::update(float elapsedTime)
{	
	for (int y = 0; y < globals::NUMBER_VERTICAL_BLOCKS; y++) {
		for (int x = 0; x < globals::NUMBER_HORIZONTAL_BLOCKS; x++) {
			if (!this->_block[y][x].isHiden()) {							// No need to look at collisions with hiden blocks
				if (this->_ball.checkBlockCollison(this->_block[y][x].getX(), this->_block[y][x].getY())) {
					this->_block[y][x].hide();
				}
			}
		}
	}
	this->_ball.update(elapsedTime, this->_paddle.getPosX(), this->_paddle.getPosY());
	this->_paddle.update(elapsedTime);
}

bool Game::allBlocksHiden()
{
	for (int y = 0; y < globals::NUMBER_VERTICAL_BLOCKS; y++) {
		for (int x = 0; x < globals::NUMBER_HORIZONTAL_BLOCKS; x++) {
			if (this->_block[y][x].isHiden() == false) {
				return false;
			}
		}
	}

	return true;
}
