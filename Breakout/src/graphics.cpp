#include <SDL.h>
#include "SDL_image.h"
#include "../headers/graphics.h"
#include "../headers/globals.h"


/* Graphics Class
* Holds all the information dealing with graphics for the game
*/

Graphics::Graphics()
{
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &_window, &_renderer); // Instead of &_renderer you can use &this->_renderer, but you do not need that.
	SDL_SetWindowTitle(_window, "Breakout");
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(_window);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath) {
	if (this->_spriteSheets.count(filePath) == 0) {
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this->_spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture * texture, SDL_Rect * sourceRectangle, SDL_Rect * destinationRectangle)
{
	SDL_RenderCopy(this->_renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip()
{
	SDL_RenderPresent(this->_renderer);
}

void Graphics::clear()
{
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer * Graphics::getRenderer() const
{
	return this->_renderer;
}
