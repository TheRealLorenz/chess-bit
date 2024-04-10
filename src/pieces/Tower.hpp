#pragma once

#include "../Board.hpp"

class Tower : public virtual Board::Piece {
public:
    Tower(Cell cell, Color color, bool hasMoved = false, const int sizePx = 50);

    virtual std::vector<Move> getMoves(const Board& board) const override;
};
