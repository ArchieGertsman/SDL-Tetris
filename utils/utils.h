#pragma once
#include <SDL/SDL_image.h>
#include <random>
#include <iostream>
#include "window.h"
#include "../src/piece.h"

namespace Utils
{
	static const int INFO_PANEL_WIDTH = 150;
	static const int SCR_WIDTH = 10 * BLOCK_WIDTH + INFO_PANEL_WIDTH;
	static const int SCR_HEIGHT = 20 * BLOCK_HEIGHT;

	inline int randomNumber(int min, int max) {
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
		return dist(rng);
	}

	inline SDL_Texture *loadTexture(const std::string &file_path) {
		auto surface = IMG_Load(file_path.c_str());
		if (!surface)
			std::cout << "failed to create board\'s surface\n";
		
		auto texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
		if (!texture)
			std::cout << "failed to create board\'s texture\n";
		
		SDL_FreeSurface(surface);
		return texture;
	}

	inline int roundDown(int num, int multiple) {
		return (num / multiple) * multiple;
	}
}