#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

#include "Piece.hpp"

class Tower : public virtual Piece {
public:
    Tower(Cell cell, Color color, const int size = 50);

    virtual std::vector<std::vector<Cell>> getMoves() const;
};
