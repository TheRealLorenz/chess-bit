#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

#include "Bishop.hpp"
#include "Tower.hpp"

class Queen : public Tower, public Bishop {
public:
    Queen(Cell cell, Color color, const int size = 50);

    virtual std::vector<std::vector<Cell>> getMoves() const;
};
