#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

#include "Piece.hpp"

class Pawn : public Piece {
public:
    Pawn(Cell cell, Color color, const int size = 50);

    virtual std::vector<std::vector<Cell>> getMoves() const;
    virtual void setCell(Cell cell);

private:
    bool firstMove = true;
};
