#include "Pawn.hpp"

Pawn::Pawn(Cell cell, Color color, bool hasMoved, const int size)
    : Piece(cell, color, hasMoved, size) {
    loadTexture(Type::Pawn);
}

std::vector<Move> Pawn::getMoves(
    const std::vector<std::shared_ptr<Piece>>& pieces) const {
    std::vector<Move> moves;
    const int maxDistance = hasMoved ? 1 : 2;
    moves.reserve(4);

    switch (color) {
        case Piece::Color::White: {
            for (int i = 1; i <= std::min(row, maxDistance); i++) {
                moves.push_back(Move({row - i, column}));
            }
            if (row > 0) {
                if (column > 0 && pieces[(row - 1) * 8 + column - 1] &&
                    pieces[(row - 1) * 8 + column - 1]->getColor() != color) {
                    moves.push_back(Move({row - 1, column - 1}));
                }
                if (column < 7 && pieces[(row - 1) * 8 + column + 1] &&
                    pieces[(row - 1) * 8 + column + 1]->getColor() != color) {
                    moves.push_back(Move({row - 1, column + 1}));
                }
            }
            break;
        }
        case Piece::Color::Black: {
            for (int i = 1; i <= std::min(7 - row, maxDistance); i++) {
                moves.push_back(Move({row + i, column}));
            }
            if (row < 7) {
                if (column > 0 && pieces[(row + 1) * 8 + column - 1] &&
                    pieces[(row + 1) * 8 + column - 1]->getColor() != color) {
                    moves.push_back(Move({row + 1, column - 1}));
                }
                if (column < 7 && pieces[(row + 1) * 8 + column + 1] &&
                    pieces[(row + 1) * 8 + column + 1]->getColor() != color) {
                    moves.push_back(Move({row + 1, column + 1}));
                }
            }
            break;
        }
    }

    return moves;
}
