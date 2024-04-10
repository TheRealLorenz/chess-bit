#pragma once

#include "../Board.hpp"

class King : public Board::Piece {
public:
    King(Cell cell, Color color, bool hasMoved = false, const int sizePx = 50);

    std::vector<Move> getMoves(const Board& board) const override;
};
