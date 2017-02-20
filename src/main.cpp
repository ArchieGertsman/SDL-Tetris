#include <SDL/SDL.h>
#include "../utils/utils.h"
#include "../utils/window.h"
#include "board.h"

int main(int argc, char **argv) {
	Window window("Tetris (Archie)", Utils::SCR_WIDTH, Utils::SCR_HEIGHT);
	Board board;

	while (!window.closed()) {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			window.pollEvents(event);
			if (!board.isGameOver()) {
				board.pollEvents(event);
			}
		}
		window.clear();
		board.draw();
		!board.isGameOver() ? board.update() : board.showGameOverMessage();
	}

	return 0;
}