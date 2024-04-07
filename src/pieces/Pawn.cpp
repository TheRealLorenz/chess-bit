#include "Pawn.hpp"

Pawn::Pawn(Cell cell, Color color, const int size) : Piece(cell, color, size) {
    loadTexture(Type::Pawn);
}

std::vector<std::vector<Cell>> Pawn::getMoves() const {
    auto moves = std::vector<std::vector<Cell>>(1);

    switch (color) {
        case Piece::Color::White: {
            if (row > 0) {
                moves[0].push_back({row - 1, column});
            }
            break;
        }
        case Piece::Color::Black: {
            if (row < 7) {
                moves[0].push_back({row + 1, column});
            }
            break;
        }
    }

    return moves;
}

void Pawn::setCell(Cell cell) {
    Piece::setCell(cell);
    firstMove = false;
}
