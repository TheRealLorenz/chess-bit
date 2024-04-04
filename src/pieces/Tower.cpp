#include "Tower.hpp"

Tower::Tower(Cell cell, Color color, const int size)
    : Piece(cell, color, size) {
    loadTexture(Type::Tower);
}

std::vector<std::vector<Cell>> Tower::getMoves() const {
    auto moves = std::vector<std::vector<Cell>>(4);

    // From piece to right border
    for (int i = 1; i < 8 - column; i++) {
        moves[0].push_back({row, column + i});
    }
    // From piece to left border
    for (int i = 1; i <= column; i++) {
        moves[1].push_back({row, column - i});
    }
    // From piece to upper border
    for (int i = 1; i <= row; i++) {
        moves[2].push_back({row - i, column});
    }
    // From piece to lower border
    for (int i = 1; i < 8 - row; i++) {
        moves[3].push_back({row + i, column});
    }

    return moves;
}
