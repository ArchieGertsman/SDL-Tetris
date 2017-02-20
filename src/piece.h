#pragma once

#include <SDL/SDL.h>
#include <vector>
#include "../utils/window.h"
#include <map>
#include <memory>
#include "block.h"

namespace {
	typedef std::shared_ptr<Block> BlockPtr;
}

class Piece {
public:
	struct Shape;

	Piece() { }
	Piece(const Shape &shape, int screen_width, int y);
	void calculateDimensions();
	void draw() const;
	void moveDown();
	void moveLeft();
	void moveRight();
	void rotate();

	inline int getY() const { return _y; }
	inline int getX() const { return _x; }
	inline int getWidth() const { return _width; }
	inline int getHeight() const { return _height; }
	inline Shape getShape() const { return _shape; }
	inline const std::vector<BlockPtr> &getBlocks() const { return _blocks; }

	void setPos(int x, int y);

private:
	static int NUM_BLOCKS;
	int _x = 0, _y = 0;
	int _width = 0, _height = 0;
	std::vector<BlockPtr> _blocks;

public:
	struct Shape {
		static Shape T;
		static Shape I;
		static Shape L;
		static Shape J;
		static Shape O;
		static Shape S;
		static Shape Z;
		static std::map<int, Shape> number_shape_map;

	private:
		struct Point {
			int x, y;
			bool operator!=(const Point &point) {
				return !(point.x == this->x && point.y == this->y);
			}
		};

	public:
		Shape() { }
		Shape(const std::vector<Point> &locations, const SDL_Color &color) :
			block_locations(locations), color(color) { }

		bool operator!=(Shape shape) {
			for (auto i = 0; i < 4; ++i) {
				if (shape.block_locations[i] != this->block_locations[i]) {
					return true;
				}
			}
			return false;
		}

		bool operator==(Shape shape) {
			for (auto i = 0; i < 4; ++i) {
				if (shape.block_locations[i] != this->block_locations[i]) {
					return false;
				}
			}
			return true;
		}

		std::vector<Point> block_locations;
		SDL_Color color;
	};

private:
	Shape _shape;
};