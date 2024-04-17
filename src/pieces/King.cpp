#include <algorithm>

#include "King.hpp"

King::King(Cell cell, Color color, bool hasMoved, const int sizePx)
    : Piece(cell, color, hasMoved, sizePx) {
    loadTexture(Type::King);
}

std::vector<Move> King::getMoves(const Board& board) const {
    std::vector<Move> moves;
    moves.reserve(8);

    Board boardWithoutKing = Board(board);
    boardWithoutKing.capturePiece({row, column});

    Color otherColor;
    switch (color) {
        case Board::Piece::Color::White:
            otherColor = Board::Piece::Color::Black;
            break;
        case Board::Piece::Color::Black:
            otherColor = Board::Piece::Color::White;
            break;
    }

    if (!moved && !boardWithoutKing.isUnderAttack({row, column}, otherColor)) {
        if (board.getPiece({row, 0}) && !board.getPiece({row, 0})->hasMoved() &&
            !boardWithoutKing.isUnderAttack({row, 0}, otherColor)) {
            bool valid = true;
            for (int i = 1; i < column; i++) {
                if (board.getPiece({row, i}) ||
                    boardWithoutKing.isUnderAttack({row, i}, otherColor)) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                moves.push_back(Move({row, 0}, Move::Type::LongCastling));
            }
        }

        if (board.getPiece({row, 7}) && !board.getPiece({row, 7})->hasMoved() &&
            !boardWithoutKing.isUnderAttack({row, 7}, otherColor)) {
            bool valid = true;
            for (int i = column + 1; i < 7; i++) {
                if (board.getPiece({row, i}) ||
                    boardWithoutKing.isUnderAttack({row, i}, otherColor)) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                moves.push_back(Move({row, 7}, Move::Type::ShortCastling));
            }
        }
    }

    for (int i = std::max(0, row - 1); i <= std::min(7, row + 1); i++) {
        for (int j = std::max(0, column - 1); j <= std::min(7, column + 1);
             j++) {
            if (i == row && j == column ||
                (board.getPiece({i, j}) &&
                 board.getPiece({i, j})->getColor() == color))
                continue;

            moves.push_back(Move({i, j}));
        }
    }

    return moves;
}
