#include "pieces/Pawn.hpp"

Pawn::Pawn(Cell cell, Color color, bool hasMoved, const int sizePx)
    : Piece(cell, color, hasMoved, sizePx) {
    loadTexture(Type::Pawn);
}

std::vector<Move> Pawn::getMoves(const Board& board) const {
    std::vector<Move> moves;
    moves.reserve(4);

    switch (color) {
        case Piece::Color::White: {
            if (row > 0 &&
                !(board.getPiece({row - 1, column}) &&
                  board.getPiece({row - 1, column})->getColor() == color)) {
                moves.push_back(Move({row - 1, column}));
            }
            if (row > 1 && !moved &&
                !(board.getPiece({row - 2, column}) &&
                  board.getPiece({row - 2, column})->getColor() == color)) {
                moves.push_back(
                    Move({row - 2, column}, Move::Type::DoublePawn));
            }
            if (row > 0) {
                if (column > 0) {
                    if (board.getPiece({row - 1, column - 1}) &&
                        board.getPiece({row - 1, column - 1})->getColor() !=
                            color) {
                        moves.push_back(Move({row - 1, column - 1}));
                    } else if (board.getCapturableEnPassant() &&
                               board.getCapturableEnPassant()->getColor() !=
                                   color &&
                               board.getCapturableEnPassant()->getCell() ==
                                   Cell{row, column - 1}) {
                        moves.push_back(Move({row - 1, column - 1},
                                             Move::Type::EnPassantCapture));
                    }
                }
                if (column < 7) {
                    if (board.getPiece({row - 1, column + 1}) &&
                        board.getPiece({row - 1, column + 1})->getColor() !=
                            color) {
                        moves.push_back(Move({row - 1, column + 1}));
                    } else if (board.getCapturableEnPassant() &&
                               board.getCapturableEnPassant()->getColor() !=
                                   color &&
                               board.getCapturableEnPassant()->getCell() ==
                                   Cell{row, column + 1}) {
                        moves.push_back(Move({row - 1, column + 1},
                                             Move::Type::EnPassantCapture));
                    }
                }
            }
            break;
        }
        case Piece::Color::Black: {
            if (row < 7) {
                moves.push_back(Move({row + 1, column}));
            }
            if (row < 6 && !moved) {
                moves.push_back(
                    Move({row + 2, column}, Move::Type::DoublePawn));
            }
            if (row < 7) {
                if (column > 0) {
                    if (board.getPiece({row + 1, column - 1}) &&
                        board.getPiece({row + 1, column - 1})->getColor() !=
                            color) {
                        moves.push_back(Move({row + 1, column - 1}));
                    } else if (board.getCapturableEnPassant() &&
                               board.getCapturableEnPassant()->getColor() !=
                                   color &&
                               board.getCapturableEnPassant()->getCell() ==
                                   Cell{row, column - 1}) {
                        moves.push_back(Move({row + 1, column - 1},
                                             Move::Type::EnPassantCapture));
                    }
                }
                if (column < 7) {
                    if (board.getPiece({row + 1, column + 1}) &&
                        board.getPiece({row + 1, column + 1})->getColor() !=
                            color) {
                        moves.push_back(Move({row + 1, column + 1}));
                    } else if (board.getCapturableEnPassant() &&
                               board.getCapturableEnPassant()->getColor() !=
                                   color &&
                               board.getCapturableEnPassant()->getCell() ==
                                   Cell{row, column + 1}) {
                        moves.push_back(Move({row + 1, column + 1},
                                             Move::Type::EnPassantCapture));
                    }
                }
            }
            break;
        }
    }

    return moves;
}
