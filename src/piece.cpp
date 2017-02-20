#include "piece.h"
#include <iostream>
#include "../utils/utils.h"

int Piece::NUM_BLOCKS = 4;

Piece::Shape Piece::Shape::T = Piece::Shape({	{ 1, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }	},	SDL_Color{ 150,  0,  255 }); // violet
Piece::Shape Piece::Shape::I = Piece::Shape({	{ 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 }	},	SDL_Color{  0,  215, 255 }); // cyan
Piece::Shape Piece::Shape::L = Piece::Shape({	{ 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 3 }	},	SDL_Color{ 255, 125,  0  }); // orange
Piece::Shape Piece::Shape::J = Piece::Shape({	{ 1, 1 }, { 1, 2 }, { 1, 3 }, { 0, 3 }	},	SDL_Color{  0,   0,  255 }); // blue
Piece::Shape Piece::Shape::O = Piece::Shape({	{ 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 }	},	SDL_Color{ 255, 50,  255 }); // pink
Piece::Shape Piece::Shape::S = Piece::Shape({	{ 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 }	},	SDL_Color{  0,  255,  0  }); // green
Piece::Shape Piece::Shape::Z = Piece::Shape({	{ 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 }	},	SDL_Color{ 255,  0,   0  }); // red

std::map<int, Piece::Shape> Piece::Shape::number_shape_map = {
	{ 0, Shape::T },
	{ 1, Shape::I },
	{ 2, Shape::L },
	{ 3, Shape::J },
	{ 4, Shape::O },
	{ 5, Shape::S },
	{ 6, Shape::Z },
};

Piece::Piece(const Shape &shape, int screen_width, int y) 
	: _shape(shape) 
{
	_x = Utils::roundDown( (screen_width - _width) / 2, BLOCK_WIDTH);
	_y = y;

	for (const auto &block_location : shape.block_locations) {
		_blocks.push_back(BlockPtr(new Block(	
			_x + BLOCK_WIDTH  * block_location.x, 
			_y + BLOCK_HEIGHT * block_location.y,
			shape.color	
		)));
	}

	calculateDimensions();
}

static std::pair<int, int> getMaxCoords(const std::vector<BlockPtr> &blocks);
static std::pair<int, int> getMinCoords(const std::vector<BlockPtr> &blocks);

void Piece::rotate() {
	std::pair<int, int> max_coords = getMaxCoords(_blocks);

	int x_pivot = Utils::roundDown((_x + max_coords.first + BLOCK_WIDTH) / 2, BLOCK_WIDTH );
	int y_pivot = Utils::roundDown((_y + max_coords.second)			  / 2, BLOCK_HEIGHT);

	for (int i = 0; i < NUM_BLOCKS; ++i) {
		int x1 = y_pivot - _blocks[i]->getY();
		int y1 = _blocks[i]->getX() - x_pivot;

		_blocks[i]->setPos(x_pivot + x1, y_pivot + y1);
	}

	calculateDimensions();
}

void Piece::calculateDimensions() {
	std::pair<int, int> max_coords = getMaxCoords(_blocks);
	std::pair<int, int> min_coords = getMinCoords(_blocks);

	_x = min_coords.first;
	_y = min_coords.second;

	_width  = max_coords.first  + BLOCK_WIDTH  - _x;
	_height = max_coords.second + BLOCK_HEIGHT - _y;
}

void Piece::draw() const {
	for (const auto &b : _blocks) {
		b->draw();
	}
}

void Piece::moveDown() {
	for (auto &b : _blocks) {
		b->moveDown();
	}
	_y += BLOCK_HEIGHT;
}

void Piece::moveLeft() {
	for (auto &b : _blocks) {
		b->moveLeft();
	}
	_x -= BLOCK_HEIGHT;
}

void Piece::moveRight() {
	for (auto &b : _blocks) {
		b->moveRight();
	}
	_x += BLOCK_HEIGHT;
}

void Piece::setPos(int x, int y) {
	int dx = x - this->_x;
	int dy = y - this->_y;

	_x = x;
	_y = y;

	for (auto &b : _blocks) {
		b->setPos(b->getX() + dx, b->getY() + dy);
	}
}

std::pair<int, int> getMaxCoords(const std::vector<BlockPtr> &blocks) {
	int x_max = 0;
	int y_max = 0;

	for (const auto &b : blocks) {
		if (b->getX() > x_max) {
			x_max = b->getX();
		}

		if (b->getY() > y_max) {
			y_max = b->getY();
		}
	}

	return std::make_pair(x_max, y_max);
}

std::pair<int, int> getMinCoords(const std::vector<BlockPtr> &blocks) {
	int x_min = 1000;
	int y_min = 1000;

	for (const auto &b : blocks) {
		if (b->getX() < x_min) {
			x_min = b->getX();
		}

		if (b->getY() < y_min) {
			y_min = b->getY();
		}
	}

	return std::make_pair(x_min, y_min);
}