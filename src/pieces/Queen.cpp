#include <iterator>

#include "Queen.hpp"

Queen::Queen(Cell cell, Color color, bool hasMoved, const int size)
    : Piece(cell, color, hasMoved, size),
      Tower(cell, color, hasMoved, size),
      Bishop(cell, color, hasMoved, size) {
    Tower::loadTexture(Type::Queen);
}

std::vector<Move> Queen::getMoves(
    const std::vector<std::shared_ptr<Piece>>& pieces,
    const std::shared_ptr<Piece>& enPassant) const {
    auto moves = Tower::getMoves(pieces, enPassant);
    auto diagonalMoves(Bishop::getMoves(pieces, enPassant));
    // For performance
    moves.reserve(moves.size() +
                  std::distance(diagonalMoves.begin(), diagonalMoves.end()));
    moves.insert(moves.end(), diagonalMoves.begin(), diagonalMoves.end());

    return moves;
}
