#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

#include "Piece.hpp"

class Pawn : public Piece {
public:
    Pawn(int row, int column, Color color, const int size = 50);

    virtual std::vector<sf::Vector2u> getMoves() const;
};
