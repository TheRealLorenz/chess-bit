#pragma once

#include "Board.hpp"

class Knight : public Board::Piece {
public:
    Knight(Cell cell, Color color, bool hasMoved = false,
           const int sizePx = 50);

    std::vector<Move> getMoves(const Board& board) const override;
};
