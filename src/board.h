#pragma once

#include <SDL/SDL.h>
#include "piece.h"
#include "../utils/utils.h"
#include <vector>
#include "../utils/text.h"
#include "info_panel.h"

#define BOARD_WIDTH_PX	(Board::WIDTH * BLOCK_WIDTH)
#define BOARD_HEIGHT_PX	(Board::HEIGHT * BLOCK_HEIGHT)

class Board {
public:
	Board();

	void update();
	void pollEvents(const SDL_Event &event);
	void draw() const;
	void clearRows();
	void generateNewPiece();
	void updateHighestRow();
	bool checkVerticalCollision();
	bool checkLeftCollision();
	bool checkRightCollision();

	inline bool isGameOver() const { return _game_over; }
	void showGameOverMessage() const;

public:
	static int WIDTH;
	static int HEIGHT;

private:
	InfoPanel _info_panel;
	Piece _current_piece;
	Piece _next_piece = Piece(Piece::Shape::number_shape_map[Utils::randomNumber(0, 6)], BOARD_WIDTH_PX, BLOCK_HEIGHT);;
	std::vector<std::vector<BlockPtr>> _blocks;

private:
	double _timer = 0;
	double _speed = 6;
	bool _paused = false;
	bool _game_over = false;
	int _highest_row = 0;

private:
	SDL_Rect _background_rect = SDL_Rect{ 0, 0, BOARD_WIDTH_PX, BOARD_HEIGHT_PX };
	Text _paused_message = Text("res/comic.ttf", 36, "Paused", SDL_Color{ 0, 0, 255 });
	Text _game_over_message = Text("res/comic.ttf", 36, "Game Over", SDL_Color{ 255, 0, 0 });
};