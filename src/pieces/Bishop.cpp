#include <algorithm>

#include "Bishop.hpp"

Bishop::Bishop(Cell cell, Color color, bool hasMoved, const int size)
    : Piece(cell, color, hasMoved, size) {
    loadTexture(Type::Bishop);
}

std::vector<Cell> Bishop::getMoves(
    const std::vector<std::shared_ptr<Piece>>& pieces) const {
    std::vector<Cell> moves;

    // From piece to top-right border
    for (int i = 1; i < std::min(8 - column, row + 1); i++) {
        moves.push_back({row - i, column + i});

        auto otherPiece = pieces[(row - i) * 8 + column + i];
        if (!otherPiece) continue;

        if (otherPiece->getColor() == color) {
            moves.pop_back();
        }
        break;
    }
    // From piece to top-left border
    for (int i = 1; i < std::min(column + 1, row + 1); i++) {
        moves.push_back({row - i, column - i});

        auto otherPiece = pieces[(row - i) * 8 + column - i];
        if (!otherPiece) continue;

        if (otherPiece->getColor() == color) {
            moves.pop_back();
        }
        break;
    }
    // From piece to bottom-right border
    for (int i = 1; i < std::min(8 - column, 8 - row); i++) {
        moves.push_back({row + i, column + i});

        auto otherPiece = pieces[(row + i) * 8 + column + i];
        if (!otherPiece) continue;

        if (otherPiece->getColor() == color) {
            moves.pop_back();
        }
        break;
    }
    // From piece to bottom-left border
    for (int i = 1; i < std::min(column + 1, 8 - row); i++) {
        moves.push_back({row + i, column - i});

        auto otherPiece = pieces[(row + i) * 8 + column - i];
        if (!otherPiece) continue;

        if (otherPiece->getColor() == color) {
            moves.pop_back();
        }
        break;
    }

    return moves;
}
