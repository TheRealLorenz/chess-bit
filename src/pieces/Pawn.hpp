#pragma once

#include <SFML/System/Vector2.hpp>

#include "Piece.hpp"

class Pawn : public Piece {
public:
    Pawn(Cell cell, Color color, bool hasMoved = false, const int size = 50);

    std::vector<Move> getMoves(
        const std::vector<std::shared_ptr<Piece>>& pieces,
        const std::shared_ptr<Piece>& enPassant) const override;
};
