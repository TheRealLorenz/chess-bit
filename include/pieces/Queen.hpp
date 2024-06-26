#pragma once

#include "Bishop.hpp"
#include "Tower.hpp"

class Queen : public Tower, public Bishop {
public:
    Queen(Cell cell, Color color, bool hasMoved = false, const int sizePx = 50);

    std::vector<Move> getMoves(const Board& board) const override;
};
