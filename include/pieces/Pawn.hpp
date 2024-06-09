#pragma once

#include "Piece.hpp"

class Pawn : public Piece {
public:
    Pawn(Cell cell, Color color, bool hasMoved = false, const int sizePx = 50);

    std::vector<Move> getMoves(const Board& board) const override;
};
