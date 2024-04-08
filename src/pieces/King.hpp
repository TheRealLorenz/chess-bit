#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

#include "Piece.hpp"

class King : public Piece {
public:
    King(Cell cell, Color color, bool hasMoved = false, const int size = 50);

    virtual std::vector<Cell> getMoves(
        const std::vector<std::shared_ptr<Piece>>& pieces) const;
};
