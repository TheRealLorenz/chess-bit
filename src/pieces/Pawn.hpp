#pragma once

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

#include "Piece.hpp"

class Pawn : public Piece {
public:
    Pawn(Cell cell, Color color, const int size = 50);

    virtual std::vector<Cell> getMoves(
        const std::vector<std::shared_ptr<Piece>>& pieces) const;
    virtual void setCell(Cell cell);

private:
    bool firstMove = true;
};
