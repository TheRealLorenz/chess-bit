#include "pieces/Pawn.hpp"

#include "Board.hpp"

Pawn::Pawn(Cell cell, Color color, bool hasMoved, const int sizePx)
    : Piece(cell, color, hasMoved, sizePx) {
    loadTexture(Type::Pawn);
}

std::vector<Move> Pawn::getMoves(const Board& board) const {
    std::vector<Move> moves;
    moves.reserve(4);

    int rowDirection = 0;
    switch (color) {
        case Color::White:
            rowDirection = -1;
            break;
        case Color::Black:
            rowDirection = 1;
            break;
    }

    int nextRow = row + rowDirection;
    if (nextRow < 0 || nextRow > 7) {
        return moves;
    }

    auto isEnemy = [&board, this](const Cell& cell) {
        const auto& piece = board.getPiece(cell);

        return piece && piece->getColor() != color;
    };
    auto isEmpty = [&board](const Cell& cell) { return !board.getPiece(cell); };
    auto isLegalCell = [](const Cell& cell) {
        if (cell.row < 0 || cell.row > 7) return false;
        if (cell.column < 0 || cell.column > 7) return false;

        return true;
    };

    if (isEmpty({nextRow, column})) {
        moves.emplace_back(Cell{nextRow, column});

        int doubleStride = nextRow + rowDirection;
        if (!moved && isLegalCell({doubleStride, column}) &&
            isEmpty({doubleStride, column})) {
            moves.emplace_back(Cell{doubleStride, column},
                               Move::Type::DoublePawn);
        }
    }

    for (auto& columnDirection : {-1, 1}) {
        int nextColumn = column + columnDirection;

        if (!isLegalCell({nextRow, nextColumn})) continue;

        if (isEnemy({nextRow, nextColumn})) {
            moves.emplace_back(Cell{nextRow, nextColumn});
            continue;
        }

        auto& enPassant = board.getCapturableEnPassant();
        if (!enPassant) continue;
        if (enPassant->getColor() == color) continue;
        if (enPassant->getCell() != Cell{row, nextColumn}) continue;

        moves.emplace_back(Cell{nextRow, nextColumn},
                           Move::Type::EnPassantCapture);
    }

    return moves;
}
