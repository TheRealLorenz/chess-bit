#pragma once

#include "Piece.hpp"

class Tower : public virtual Piece {
public:
    Tower(Cell cell, Color color, bool hasMoved = false, const int sizePx = 50);

    virtual std::vector<Move> getMoves(const Board& board) const override;
};
