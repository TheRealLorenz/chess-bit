#include "King.hpp"

King::King(Cell cell, Color color, const int size) : Piece(cell, color, size) {
    loadTexture(Type::King);
}

std::vector<std::vector<Cell>> King::getMoves() const {
    auto moves = std::vector<std::vector<Cell>>(4);
    int idx = 0;

    if (row > 0) {
        if (column > 0) {
            moves[idx++].push_back({row - 1, column - 1});
        }
        if (column < 7) {
            moves[idx++].push_back({row - 1, column + 1});
        }
    }

    if (row < 7) {
        if (column > 0) {
            moves[idx++].push_back({row + 1, column - 1});
        }
        if (column < 7) {
            moves[idx++].push_back({row + 1, column + 1});
        }
    }

    return moves;
}
