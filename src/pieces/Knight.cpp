#include "Knight.hpp"

Knight::Knight(Cell cell, Color color, bool hasMoved, const int size)
    : Piece(cell, color, hasMoved, size) {
    loadTexture(Type::Knight);
}

std::vector<Move> Knight::getMoves(
    const std::vector<std::shared_ptr<Piece>>& pieces,
    const std::shared_ptr<Piece>& enPassant) const {
    std::vector<Move> moves;
    moves.reserve(8);

    // Top
    if (row > 1) {
        if (column > 0 &&
            (!pieces[(row - 2) * 8 + column - 1] ||
             pieces[(row - 2) * 8 + column - 1]->getColor() != color)) {
            moves.push_back(Move({row - 2, column - 1}));
        }
        if (column < 7 &&
            (!pieces[(row - 2) * 8 + column + 1] ||
             pieces[(row - 2) * 8 + column + 1]->getColor() != color)) {
            moves.push_back(Move({row - 2, column + 1}));
        }
    }

    // Right
    if (column < 6) {
        if (row > 0 &&
            (!pieces[(row - 1) * 8 + column + 2] ||
             pieces[(row - 1) * 8 + column + 2]->getColor() != color)) {
            moves.push_back(Move({row - 1, column + 2}));
        }
        if (row < 7 &&
            (!pieces[(row + 1) * 8 + column + 2] ||
             pieces[(row + 1) * 8 + column + 2]->getColor() != color)) {
            moves.push_back(Move({row + 1, column + 2}));
        }
    }

    // Bottom
    if (row < 6) {
        if (column > 0 &&
            (!pieces[(row + 2) * 8 + column - 1] ||
             pieces[(row + 2) * 8 + column - 1]->getColor() != color)) {
            moves.push_back(Move({row + 2, column - 1}));
        }
        if (column < 7 &&
            (!pieces[(row + 2) * 8 + column + 1] ||
             pieces[(row + 2) * 8 + column + 1]->getColor() != color)) {
            moves.push_back(Move({row + 2, column + 1}));
        }
    }

    // Left
    if (column > 1) {
        if (row > 0 &&
            (!pieces[(row - 1) * 8 + column - 2] ||
             pieces[(row - 1) * 8 + column - 2]->getColor() != color)) {
            moves.push_back(Move({row - 1, column - 2}));
        }
        if (row < 7 &&
            (!pieces[(row + 1) * 8 + column - 2] ||
             pieces[(row + 1) * 8 + column - 2]->getColor() != color)) {
            moves.push_back(Move({row + 1, column - 2}));
        }
    }

    return moves;
}
