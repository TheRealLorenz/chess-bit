#include <iterator>

#include "Queen.hpp"

Queen::Queen(Cell cell, Color color, const int size)
    : Piece(cell, color, size),
      Tower(cell, color, size),
      Bishop(cell, color, size) {
    Tower::loadTexture(Type::Queen);
}

std::vector<std::vector<Cell>> Queen::getMoves() const {
    auto moves = Tower::getMoves();
    auto diagonalMoves(Bishop::getMoves());
    // For performance
    moves.reserve(moves.size() +
                  std::distance(diagonalMoves.begin(), diagonalMoves.end()));
    moves.insert(moves.end(), diagonalMoves.begin(), diagonalMoves.end());

    return moves;
}
