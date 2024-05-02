#include "Queen.hpp"

#include <iterator>

Queen::Queen(Cell cell, Color color, bool hasMoved, const int sizePx)
    : Piece(cell, color, hasMoved, sizePx),
      Tower(cell, color, hasMoved, sizePx),
      Bishop(cell, color, hasMoved, sizePx) {
    Tower::loadTexture(Type::Queen);
}

std::vector<Move> Queen::getMoves(const Board& board) const {
    auto moves = Tower::getMoves(board);
    auto diagonalMoves(Bishop::getMoves(board));
    // For performance
    moves.reserve(moves.size() +
                  std::distance(diagonalMoves.begin(), diagonalMoves.end()));
    moves.insert(moves.end(), diagonalMoves.begin(), diagonalMoves.end());

    return moves;
}
