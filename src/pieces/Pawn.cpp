#include "Pawn.hpp"

Pawn::Pawn(Cell cell, Color color, bool hasMoved, const int size)
    : Piece(cell, color, hasMoved, size) {
    loadTexture(Type::Pawn);
}

std::vector<Move> Pawn::getMoves(
    const std::vector<std::shared_ptr<Piece>>& pieces,
    const std::shared_ptr<Piece>& enPassant) const {
    std::vector<Move> moves;
    moves.reserve(4);

    switch (color) {
        case Piece::Color::White: {
            if (column > 0) {
                moves.push_back(Move({row - 1, column}));
            }
            if (column > 1 && !hasMoved) {
                moves.push_back(
                    Move({row - 2, column}, Move::Type::DoublePawn));
            }
            if (row > 0) {
                if (column > 0) {
                    if (pieces[(row - 1) * 8 + column - 1] &&
                        pieces[(row - 1) * 8 + column - 1]->getColor() !=
                            color) {
                        moves.push_back(Move({row - 1, column - 1}));
                    } else if (enPassant && enPassant->getColor() != color &&
                               enPassant->getCell() == Cell{row, column - 1}) {
                        moves.push_back(Move({row - 1, column - 1},
                                             Move::Type::EnPassantCapture));
                    }
                }
                if (column < 7) {
                    if (pieces[(row - 1) * 8 + column + 1] &&
                        pieces[(row - 1) * 8 + column + 1]->getColor() !=
                            color) {
                        moves.push_back(Move({row - 1, column + 1}));
                    } else if (enPassant && enPassant->getColor() != color &&
                               enPassant->getCell() == Cell{row, column + 1}) {
                        moves.push_back(Move({row - 1, column + 1},
                                             Move::Type::EnPassantCapture));
                    }
                }
            }
            break;
        }
        case Piece::Color::Black: {
            if (column < 7) {
                moves.push_back(Move({row + 1, column}));
            }
            if (column < 6 && !hasMoved) {
                moves.push_back(
                    Move({row + 2, column}, Move::Type::DoublePawn));
            }
            if (row < 7) {
                if (column > 0) {
                    if (pieces[(row + 1) * 8 + column - 1] &&
                        pieces[(row + 1) * 8 + column - 1]->getColor() !=
                            color) {
                        moves.push_back(Move({row + 1, column - 1}));
                    } else if (enPassant && enPassant->getColor() != color &&
                               enPassant->getCell() == Cell{row, column - 1}) {
                        moves.push_back(Move({row + 1, column - 1},
                                             Move::Type::EnPassantCapture));
                    }
                }
                if (column < 7) {
                    if (pieces[(row + 1) * 8 + column + 1] &&
                        pieces[(row + 1) * 8 + column + 1]->getColor() !=
                            color) {
                        moves.push_back(Move({row + 1, column + 1}));
                    } else if (enPassant && enPassant->getColor() != color &&
                               enPassant->getCell() == Cell{row, column + 1}) {
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
