#include "board.h"
#include <iostream>
#include "../utils/utils.h"

int Board::WIDTH = (Utils::SCR_WIDTH - Utils::INFO_PANEL_WIDTH) / BLOCK_WIDTH;
int Board::HEIGHT = Utils::SCR_HEIGHT / BLOCK_HEIGHT;

Board::Board() {
	_blocks.resize(BOARD_HEIGHT_PX / BLOCK_HEIGHT);
	generateNewPiece();
}

void Board::update() {
	if (!_paused) {
		if ((int)_timer / 100 == 1) {
			if (_current_piece.getY() < BOARD_HEIGHT_PX - _current_piece.getHeight() && !checkVerticalCollision()) {
				clearRows();
				_current_piece.moveDown();
				_timer = 0.0;
			}
			else {
				updateHighestRow();
				generateNewPiece();
			}
		}
		_timer += _speed;
	}
}

void Board::showGameOverMessage() const {
	_game_over_message.display(
		(BOARD_WIDTH_PX - _game_over_message.getTextWidth()) / 2,
		(BOARD_HEIGHT_PX - _game_over_message.getTextHeight()) / 2,
		Window::renderer
	);
}

void Board::clearRows() {
	for (auto y = Board::HEIGHT - 1; y >= Board::HEIGHT - _highest_row; --y) {
		if (_blocks[y].size() == Board::WIDTH) {
			_blocks[y].clear();
			for (auto j = Board::HEIGHT - y + 1; j <= _highest_row; ++j) {
				for (auto &b : _blocks[Board::HEIGHT - j]) {
					b->moveDown();
				}
				_blocks[Board::HEIGHT - j + 1] = _blocks[Board::HEIGHT - j];
				_blocks[Board::HEIGHT - j].clear();
			}
			--_highest_row;
			_info_panel.incrementScore(20);
			clearRows();
		}
	}
}

bool Board::checkVerticalCollision() {
	for (const auto &block_row : _blocks) {
		for (const auto &block : block_row) {
			for (const auto &cblock : _current_piece.getBlocks()) {
				if (cblock->getX() == block->getX() &&
					cblock->getY() == block->getY() - BLOCK_HEIGHT)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Board::checkLeftCollision() {
	for (const auto &block_row : _blocks) {
		for (const auto &block : block_row) {
			for (const auto &cblock : _current_piece.getBlocks()) {
				if (cblock->getY() == block->getY() &&
					cblock->getX() == block->getX() + BLOCK_WIDTH)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Board::checkRightCollision() {
	for (const auto &block_row : _blocks) {
		for (const auto &block : block_row) {
			for (const auto &cblock : _current_piece.getBlocks()) {
				if (cblock->getY() == block->getY() &&
					(cblock->getX() == block->getX() - BLOCK_WIDTH)
					/*|| cblock->getX() == block->getX() + BLOCK_WIDTH*/)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Board::generateNewPiece() {
	for (const auto &b : _current_piece.getBlocks()) {
		_blocks[b->getY() / BLOCK_HEIGHT].push_back(b);
	}
	_current_piece = _next_piece;

	do { _next_piece = Piece(Piece::Shape::number_shape_map[Utils::randomNumber(0, 6)], BOARD_WIDTH_PX, BLOCK_HEIGHT);
	} while (_next_piece.getShape() == _current_piece.getShape());

	_info_panel.setNextPieceTo(_next_piece);
	if (_highest_row >= Board::HEIGHT - _current_piece.getY() / 20) {
		_game_over = true;
	}
}

void Board::updateHighestRow() {
	if (((BOARD_HEIGHT_PX - _current_piece.getY()) / BLOCK_HEIGHT) > _highest_row) {
		_highest_row = (BOARD_HEIGHT_PX - _current_piece.getY()) / BLOCK_HEIGHT;
	}
}

void Board::pollEvents(const SDL_Event &event) {
	if (event.type == SDL_KEYDOWN) {
		if (!_paused) {
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				if (_current_piece.getX() > 0) {
					if (!checkLeftCollision()) {
						_current_piece.moveLeft();
					}
				}
				break;
			case SDLK_RIGHT:
				if (_current_piece.getX() < BOARD_WIDTH_PX - _current_piece.getWidth()) {
					if (!checkRightCollision()) {
						_current_piece.moveRight();
					}
				}
				break;
			case SDLK_SPACE:
				while (!checkVerticalCollision() &&
					_current_piece.getY() < BOARD_HEIGHT_PX - _current_piece.getHeight())
				{
					_current_piece.moveDown();
				}
				break;
			case SDLK_UP:
				if (_current_piece.getShape() != Piece::Shape::O) {
					_current_piece.rotate();
				}
				break;
			case SDLK_DOWN:
				_speed = 36;
				break;
			}
		}
		if (event.key.keysym.sym == SDLK_p) {
			_paused = !_paused;
		}
	}

	else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN) {
		_speed = 6;
	}
}

void Board::draw() const {
	SDL_SetRenderDrawColor(Window::renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(Window::renderer, &_background_rect);
	_current_piece.draw();
	for (const auto &block_row : _blocks) {
		for (const auto &b : block_row) {
			b->draw();
		}
	}
	if (_paused) {
		_paused_message.display(
			(BOARD_WIDTH_PX - _paused_message.getTextWidth()) / 2,
			(BOARD_HEIGHT_PX - _paused_message.getTextHeight()) / 2,
			Window::renderer
		);
	}
	_info_panel.draw();
}