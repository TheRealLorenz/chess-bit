#include "Tower.hpp"

Tower::Tower(Cell cell, Color color, const int size)
    : Piece(cell, color, size) {
    loadTexture(Type::Tower);
}

std::vector<Cell> Tower::getMoves(
    const std::vector<std::shared_ptr<Piece>>& pieces) const {
    std::vector<Cell> moves;

    // From piece to right border
    for (int i = 1; i < 8 - column; i++) {
        moves.push_back({row, column + i});

        auto otherPiece = pieces[row * 8 + column + i];
        if (!otherPiece) continue;

        if (otherPiece->getColor() == color) {
            moves.pop_back();
        }

        break;
    }
    // From piece to left border
    for (int i = 1; i <= column; i++) {
        moves.push_back({row, column - i});

        auto otherPiece = pieces[row * 8 + column - i];
        if (!otherPiece) continue;

        if (otherPiece->getColor() == color) {
            moves.pop_back();
        }

        break;
    }
    // From piece to upper border
    for (int i = 1; i <= row; i++) {
        moves.push_back({row - i, column});

        auto otherPiece = pieces[(row - i) * 8 + column];
        if (!otherPiece) continue;

        if (otherPiece->getColor() == color) {
            moves.pop_back();
        }

        break;
    }
    // From piece to lower border
    for (int i = 1; i < 8 - row; i++) {
        moves.push_back({row + i, column});

        auto otherPiece = pieces[(row + i) * 8 + column];
        if (!otherPiece) continue;

        if (otherPiece->getColor() == color) {
            moves.pop_back();
        }

        break;
    }

    return moves;
}
