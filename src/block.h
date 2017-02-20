#pragma once

#include <SDL/SDL.h>
#include "../utils/window.h"

#define BLOCK_WIDTH  (Block::WIDTH  + Block::PADDING)
#define BLOCK_HEIGHT (Block::HEIGHT + Block::PADDING)

class Block {
public:
	Block() { }
	Block(int x, int y, const SDL_Color &color);

	void draw() const;
	void moveDown();
	void moveLeft();
	void moveRight();

	inline int getY() const { return block_rect.y; }
	inline int getX() const { return block_rect.x; }
	inline void setPos(int x, int y) {
		block_rect.x = x;
		block_rect.y = y;
	}

public:
	static int WIDTH;
	static int HEIGHT;
	static int PADDING;

private:
	SDL_Rect block_rect;
	SDL_Color color;
};