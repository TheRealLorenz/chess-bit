#pragma once

#include "Piece.hpp"

class Bishop : public virtual Piece {
public:
    Bishop(Cell cell, Color color, bool hasMoved = false,
           const int sizePx = 50);

    virtual std::vector<Move> getMoves(const Board& board) const override;
};
