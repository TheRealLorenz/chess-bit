#include <algorithm>

#include "King.hpp"

King::King(Cell cell, Color color, const int size) : Piece(cell, color, size) {
    loadTexture(Type::King);
}

std::vector<std::vector<Cell>> King::getMoves() const {
    auto moves = std::vector<std::vector<Cell>>(8);
    int idx = 0;

    for (int i = std::max(0, row - 1); i <= std::min(7, row + 1); i++) {
        for (int j = std::max(0, column - 1); j <= std::min(7, column + 1);
             j++) {
            if (i == row && j == column) continue;

            moves[idx++].push_back({i, j});
        }
    }

    return moves;
}