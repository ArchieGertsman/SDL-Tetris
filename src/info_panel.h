#pragma once
#include "piece.h"
#include "../utils/text.h"
#include "../utils/utils.h"

class InfoPanel {
public:
	InfoPanel();

	void draw() const;
	void setNextPieceTo(const Piece &piece);
	void incrementScore(int amount);

private:
	int _x = Utils::SCR_WIDTH - Utils::INFO_PANEL_WIDTH;
	Piece _next_piece = Piece(Piece::Shape::O, 0, 0);
	Text _score = Text("res/comic.ttf", 26, "0", SDL_Color{ 0, 0, 0 });
};