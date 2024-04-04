#include <algorithm>

#include "Bishop.hpp"

Bishop::Bishop(Cell cell, Color color, const int size)
    : Piece(cell, color, size) {
    loadTexture(Type::Bishop);
}

std::vector<std::vector<Cell>> Bishop::getMoves() const {
    auto moves = std::vector<std::vector<Cell>>(4);

    // From piece to top-right border
    for (int i = 1; i < std::min(8 - column, row + 1); i++) {
        moves[0].push_back({row - i, column + i});
    }
    // From piece to top-left border
    for (int i = 1; i < std::min(column + 1, row + 1); i++) {
        moves[1].push_back({row - i, column - i});
    }
    // From piece to bottom-right border
    for (int i = 1; i < std::min(8 - column, 8 - row); i++) {
        moves[2].push_back({row + i, column + i});
    }
    // From piece to bottom-left border
    for (int i = 1; i < std::min(column + 1, 8 - row); i++) {
        moves[3].push_back({row + i, column - i});
    }

    return moves;
}
