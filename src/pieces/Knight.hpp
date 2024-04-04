#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

#include "Piece.hpp"

class Knight : public Piece {
public:
    Knight(Cell cell, Color color, const int size = 50);

    virtual std::vector<std::vector<Cell>> getMoves() const;
};
