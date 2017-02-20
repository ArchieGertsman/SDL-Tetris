#include "info_panel.h"
#include <string>

InfoPanel::InfoPanel() {
	_next_piece.setPos((_x + Utils::SCR_WIDTH) / 2, 50);
}

void InfoPanel::draw() const {
	_next_piece.draw();
	_score.display((_x + Utils::SCR_WIDTH - _score.getTextWidth()) / 2, 200, Window::renderer);
}

void InfoPanel::setNextPieceTo(const Piece &piece) {
	_next_piece = Piece(piece.getShape(), 0, 0);
	_next_piece.setPos((_x + Utils::SCR_WIDTH - _next_piece.getWidth()) / 2, 50);
}

void InfoPanel::incrementScore(int amount) {
	_score.setText(std::to_string(std::stoi(_score.getText()) + amount));
}