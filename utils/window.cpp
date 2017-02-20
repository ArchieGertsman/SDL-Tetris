#include "window.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <iostream>

SDL_Renderer *Window::renderer = nullptr;

Window::Window(const std::string &title, int width, int height) 
	: _title(title), _width(width), _height(height)
{
	_closed = !init();
}


Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(_window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "failed to init SDL\n";
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cout << "failed to init SDL_Image\n";
		return false;
	}

	if (TTF_Init() == -1) {
		std::cout << "failed to init SDL_ttf\n";
		return false;
	}

	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);

	if (_window == nullptr) {
		std::cout << "failed to create window\n";
		return false;
	}

	renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr) {
		std::cout << "failed to create renderer\n";
		return false;
	}

	return true;
}

void Window::pollEvents(SDL_Event &event) {
	_closed = (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE));
}

void Window::clear() const {
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 215, 215, 215, 255);
	SDL_RenderClear(renderer);
}