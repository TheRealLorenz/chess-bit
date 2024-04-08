#include "Pawn.hpp"

Pawn::Pawn(Cell cell, Color color, const int size) : Piece(cell, color, size) {
    loadTexture(Type::Pawn);
}

std::vector<Cell> Pawn::getMoves(
    const std::vector<std::shared_ptr<Piece>>& pieces) const {
    std::vector<Cell> moves;
    const int maxDistance = firstMove ? 2 : 1;
    moves.reserve(4);

    switch (color) {
        case Piece::Color::White: {
            for (int i = 1; i <= std::min(row, maxDistance); i++) {
                moves.push_back({row - i, column});
            }
            if (row > 0) {
                if (column > 0 && pieces[(row - 1) * 8 + column - 1] &&
                    pieces[(row - 1) * 8 + column - 1]->getColor() != color) {
                    moves.push_back({row - 1, column - 1});
                }
                if (column < 7 && pieces[(row - 1) * 8 + column + 1] &&
                    pieces[(row - 1) * 8 + column + 1]->getColor() != color) {
                    moves.push_back({row - 1, column + 1});
                }
            }
            break;
        }
        case Piece::Color::Black: {
            for (int i = 1; i <= std::min(7 - row, maxDistance); i++) {
                moves.push_back({row + i, column});
            }
            if (row < 7) {
                if (column > 0 && pieces[(row + 1) * 8 + column - 1] &&
                    pieces[(row + 1) * 8 + column - 1]->getColor() != color) {
                    moves.push_back({row + 1, column - 1});
                }
                if (column < 7 && pieces[(row + 1) * 8 + column + 1] &&
                    pieces[(row + 1) * 8 + column + 1]->getColor() != color) {
                    moves.push_back({row + 1, column + 1});
                }
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
