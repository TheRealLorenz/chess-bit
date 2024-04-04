#include "Knight.hpp"

Knight::Knight(Cell cell, Color color, const int size)
    : Piece(cell, color, size) {
    loadTexture(Type::Knight);
}

std::vector<std::vector<Cell>> Knight::getMoves() const {
    auto moves = std::vector<std::vector<Cell>>(8);
    int idx = 0;

    // Top
    if (row > 1) {
        if (column > 0) {
            moves[idx++].push_back({row - 2, column - 1});
        }
        if (column < 7) {
            moves[idx++].push_back({row - 2, column + 1});
        }
    }

    // Right
    if (column < 6) {
        if (row > 0) {
            moves[idx++].push_back({row - 1, column + 2});
        }
        if (row < 7) {
            moves[idx++].push_back({row + 1, column + 2});
        }
    }

    // Bottom
    if (row < 6) {
        if (column > 0) {
            moves[idx++].push_back({row + 2, column - 1});
        }
        if (column < 7) {
            moves[idx++].push_back({row + 2, column + 1});
        }
    }

    // Left
    if (column > 1) {
        if (row > 0) {
            moves[idx++].push_back({row - 1, column - 2});
        }
        if (row < 7) {
            moves[idx++].push_back({row + 1, column - 2});
        }
    }

    return moves;
}
