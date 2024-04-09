#include <algorithm>

#include "King.hpp"

King::King(Cell cell, Color color, bool hasMoved, const int size)
    : Piece(cell, color, hasMoved, size) {
    loadTexture(Type::King);
}

std::vector<Move> King::getMoves(
    const std::vector<std::shared_ptr<Piece>>& pieces,
    const std::shared_ptr<Piece>& enPassant) const {
    std::vector<Move> moves;
    moves.reserve(8);

    for (int i = std::max(0, row - 1); i <= std::min(7, row + 1); i++) {
        for (int j = std::max(0, column - 1); j <= std::min(7, column + 1);
             j++) {
            if (i == row && j == column ||
                (pieces[i * 8 + j] && pieces[i * 8 + j]->getColor() == color))
                continue;

            moves.push_back(Move({i, j}));
        }
    }

    return moves;
}
