#include "pieces/Tower.hpp"

#include <tuple>

#include "Board.hpp"

Tower::Tower(Cell cell, Color color, bool hasMoved, const int sizePx)
    : Piece(cell, color, hasMoved, sizePx) {
    loadTexture(Type::Tower);
}

std::vector<Move> Tower::getMoves(const Board& board) const {
    std::vector<Move> moves;

    auto isLegalCell = [&board](const Cell& cell) {
        if (cell.row < 0 || cell.row > 7) return false;
        if (cell.column < 0 || cell.column > 7) return false;

        return true;
    };

    for (auto [rowDirection, columnDirection] :
         std::vector<std::tuple<int, int>>{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}) {
        Cell cell = {row + rowDirection, column + columnDirection};

        while (isLegalCell(cell)) {
            auto& piece = board.getPiece(cell);
            if (piece && piece->getColor() == color) break;

            moves.emplace_back(cell);

            if (piece) break;

            cell.column += columnDirection;
            cell.row += rowDirection;
        }
    }

    return moves;
}
