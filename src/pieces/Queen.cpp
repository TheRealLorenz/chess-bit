#include <iterator>

#include "Queen.hpp"

Queen::Queen(Cell cell, Color color, const int size)
    : Piece(cell, color, size),
      Tower(cell, color, size),
      Bishop(cell, color, size) {
    Tower::loadTexture(Type::Queen);
}

std::vector<Cell> Queen::getMoves(
    const std::vector<std::shared_ptr<Piece>>& pieces) const {
    auto moves = Tower::getMoves(pieces);
    auto diagonalMoves(Bishop::getMoves(pieces));
    // For performance
    moves.reserve(moves.size() +
                  std::distance(diagonalMoves.begin(), diagonalMoves.end()));
    moves.insert(moves.end(), diagonalMoves.begin(), diagonalMoves.end());

    return moves;
}
