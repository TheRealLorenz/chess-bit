#include "pieces/Bishop.hpp"

#include <algorithm>

Bishop::Bishop(Cell cell, Color color, bool hasMoved, const int sizePx)
    : Piece(cell, color, hasMoved, sizePx) {
    loadTexture(Type::Bishop);
}

std::vector<Move> Bishop::getMoves(const Board& board) const {
    std::vector<Move> moves;

    // From piece to top-right border
    for (int i = 1; i < std::min(8 - column, row + 1); i++) {
        moves.push_back(Move({row - i, column + i}));

        auto otherPiece = board.getPiece({row - i, column + i});
        if (!otherPiece) continue;

        if (otherPiece->getColor() == color) {
            moves.pop_back();
        }
        break;
    }
    // From piece to top-left border
    for (int i = 1; i < std::min(column + 1, row + 1); i++) {
        moves.push_back(Move({row - i, column - i}));

        auto otherPiece = board.getPiece({row - i, column - i});
        if (!otherPiece) continue;

        if (otherPiece->getColor() == color) {
            moves.pop_back();
        }
        break;
    }
    // From piece to bottom-right border
    for (int i = 1; i < std::min(8 - column, 8 - row); i++) {
        moves.push_back(Move({row + i, column + i}));

        auto otherPiece = board.getPiece({row + i, column + i});
        if (!otherPiece) continue;

        if (otherPiece->getColor() == color) {
            moves.pop_back();
        }
        break;
    }
    // From piece to bottom-left border
    for (int i = 1; i < std::min(column + 1, 8 - row); i++) {
        moves.push_back(Move({row + i, column - i}));

        auto otherPiece = board.getPiece({row + i, column - i});
        if (!otherPiece) continue;

        if (otherPiece->getColor() == color) {
            moves.pop_back();
        }
        break;
    }

    return moves;
}
