#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

#include "Bishop.hpp"
#include "Tower.hpp"

class Queen : public Tower, public Bishop {
public:
    Queen(Cell cell, Color color, bool hasMoved = false, const int size = 50);

    virtual std::vector<Move> getMoves(
        const std::vector<std::shared_ptr<Piece>>& pieces) const;
};
