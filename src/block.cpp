#include "block.h"

int Block::WIDTH = 23;
int Block::HEIGHT = 23;
int Block::PADDING = 2;

Block::Block(int x, int y, const SDL_Color &color) :
block_rect(SDL_Rect{ x, y, Block::WIDTH, Block::HEIGHT }), color(color)
{ }

void Block::draw() const {
	SDL_SetRenderDrawColor(Window::renderer, color.r, color.g, color.b, 255);
	SDL_RenderFillRect(Window::renderer, &this->block_rect);
}

void Block::moveDown() {
	block_rect.y += BLOCK_HEIGHT;
}

void Block::moveLeft() {
	block_rect.x -= BLOCK_WIDTH;
}

void Block::moveRight() {
	block_rect.x += BLOCK_WIDTH;
}