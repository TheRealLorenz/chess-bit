#pragma once

#include "Piece.hpp"

class King : public Piece {
public:
    King(Cell cell, Color color, bool hasMoved = false, const int sizePx = 50);

    std::vector<Move> getMoves(const Board& board) const override;
};
