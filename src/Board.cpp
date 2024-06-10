#include "Board.hpp"

#include <algorithm>
#include <memory>

#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "debug.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/King.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Queen.hpp"
#include "pieces/Tower.hpp"

const int defaultSchema[64][2] = {
    {1, 1},  {2, 1},  {3, 1},  {4, 1},  {5, 1},  {3, 1},  {2, 1},  {1, 1},
    {0, 1},  {0, 1},  {0, 1},  {0, 1},  {0, 1},  {0, 1},  {0, 1},  {0, 1},
    {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0},
    {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0},
    {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0},
    {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0},
    {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},
    {1, 0},  {2, 0},  {3, 0},  {4, 0},  {5, 0},  {3, 0},  {2, 0},  {1, 0},
};

Board::Board(const int sizePx) : sizePx(sizePx) {
    const int cellSize = sizePx / 8;

    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 8; column++) {
            baseTiles[row * 8 + column] = Tile(
                sf::Vector2f(column * cellSize, row * cellSize),
                sf::Vector2f(cellSize, cellSize),
                (column + row) % 2 == 0 ? Tile::Type::Light : Tile::Type::Dark);
        }
    }

    populate(defaultSchema);
}

const sf::FloatRect Board::getBounds() const {
    const auto scale = getScale();
    const auto position = getPosition();

    return {position.x, position.y, sizePx * scale.x, sizePx * scale.y};
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the entity's transform -- combine it with the one that was
    // passed by the caller
    states.transform *= getTransform();

    // draw the tiles
    for (const auto& tile : baseTiles) {
        target.draw(tile, states);
    }
    for (const auto& tile : highlightTiles) {
        target.draw(tile, states);
    }
    if (checkTile) {
        target.draw(checkTile.value(), states);
    }

    // draw the pieces
    for (auto& p : pieces) {
        if (p) target.draw(*p, states);
    }
}

void Board::populate(const int schema[64][2]) {
    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 8; column++) {
            if (schema[row * 8 + column][0] == -1) continue;

            auto type = Piece::Type(schema[row * 8 + column][0]);
            auto color = Color(schema[row * 8 + column][1]);

            switch (type) {
                case Piece::Type::Pawn:
                    pieces.set(
                        row, column,
                        std::shared_ptr<Piece>(new Pawn({row, column}, color)));
                    break;
                case Piece::Type::Tower:
                    pieces.set(row, column,
                               std::shared_ptr<Piece>(
                                   new Tower({row, column}, color)));
                    break;
                case Piece::Type::Knight:
                    pieces.set(row, column,
                               std::shared_ptr<Piece>(
                                   new Knight({row, column}, color)));
                    break;
                case Piece::Type::Bishop:
                    pieces.set(row, column,
                               std::shared_ptr<Piece>(
                                   new Bishop({row, column}, color)));
                    break;
                case Piece::Type::Queen:
                    pieces.set(row, column,
                               std::shared_ptr<Piece>(
                                   new Queen({row, column}, color)));
                    break;
                case Piece::Type::King:
                    auto king =
                        std::shared_ptr<Piece>(new King({row, column}, color));
                    switch (color) {
                        case Color::White:
                            whiteKing = king;
                            break;
                        case Color::Black:
                            blackKing = king;
                            break;
                    }
                    pieces.set(row, column, king);
                    break;
            }
        }
    }
}

const std::shared_ptr<Piece>& Board::getPiece(Cell cell) const {
    return pieces.get(cell.row, cell.column);
}

void Board::capturePiece(Cell cell) {
    pieces.set(cell.row, cell.column, nullptr);
    if (selectedPiece && selectedPiece->getCell() == cell) {
        selectedPiece = nullptr;
    }
    if (capturableEnPassant && capturableEnPassant->getCell() == cell) {
        capturableEnPassant = nullptr;
    }
}

void Board::highlightMoves() {
    if (!selectedPiece) return;
    highlightTiles.clear();

    auto cell = selectedPiece->getCell();
    const int cellSize = sizePx / 8;

    highlightTiles.emplace_back(
        sf::Vector2f(cell.column * cellSize, cell.row * cellSize),
        sf::Vector2f(cellSize, cellSize), Tile::Type::Highlight);

    for (auto& move : selectedPiece->getMoves(*this)) {
        if (!isMoveValid(selectedPiece, move)) continue;

        highlightTiles.emplace_back(
            sf::Vector2f(move.cell.column * cellSize, move.cell.row * cellSize),
            sf::Vector2f(cellSize, cellSize), Tile::Type::Highlight);
    }
}

bool Board::isUnderAttack(Cell cell, Color by) const {
    for (auto& p : pieces) {
        if (!p || p->getColor() != by) continue;

        auto moves = p->getMoves(*this);
        if (std::any_of(moves.begin(), moves.end(), [cell](const auto& move) {
                return move.cell == cell;
            })) {
            return true;
        }
    }

    return false;
}

void Board::setCheckCell(Cell cell) {
    const int cellSize = sizePx / 8;

    checkTile = Tile(sf::Vector2f(cell.column * cellSize, cell.row * cellSize),
                     sf::Vector2f(cellSize, cellSize), Tile::Type::Check);
}

void Board::checkForChecks(Color color) {
    checkTile = std::optional<Tile>();

    auto king = whiteKing;
    Color otherColor = Color::Black;
    if (color == Color::Black) {
        king = blackKing;
        otherColor = Color::White;
    }

    if (isUnderAttack(king->getCell(), otherColor)) {
        DEBUG("[DEBUG] King is under attack");
        setCheckCell(king->getCell());

        for (auto& piece : pieces) {
            if (!piece) continue;
            if (piece->getColor() == otherColor) continue;

            for (auto& move : piece->getMoves(*this)) {
                if (isMoveValid(piece, move)) {
                    return;
                }
            }
        }

        DEBUG("[DEBUG] Checkmate!");
        return;
    }
}

void Board::select(const std::shared_ptr<Piece>& p) {
    if (!p) return;

    selectedPiece = p;
    highlightMoves();
}

void Board::unselect() {
    selectedPiece = nullptr;
    highlightTiles.clear();
}

void Board::movePiece(const std::shared_ptr<Piece>& p, Cell cell) {
    auto oldCell = p->getCell();
    p->setCell(cell);
    pieces.set(cell.row, cell.column, p);
    pieces.set(oldCell.row, oldCell.column, nullptr);
}

bool Board::isMoveValid(const std::shared_ptr<Piece>& piece, Move move) const {
    Board testBoard = Board(*this);
    Cell oldCell = piece->getCell();
    bool hasMoved = piece->hasMoved();

    // Using a shallow copy of the Baord to check for
    // checks.
    // The copy constructor performs a copy of the
    // shared pointers, so it shouldn't be costly, but
    // we need to be careful cause it can still edit the
    // original pieces.
    testBoard.movePiece(piece, move.cell);
    bool isValid = false;

    switch (piece->getColor()) {
        case Color::Black:
            isValid = !testBoard.isUnderAttack(testBoard.blackKing->getCell(),
                                               Color::White);
            break;
        case Color::White:
            isValid = !testBoard.isUnderAttack(testBoard.whiteKing->getCell(),
                                               Color::Black);
            break;
    }

    // Reset piece
    piece->setCell(oldCell);
    piece->setMoved(hasMoved);
    return isValid;
}

void Board::advanceTurn() {
    turn = turn == Color::White ? Color::Black : Color::White;
}

void Board::onClick(const sf::Event& event) {
    const auto boardPosition = getPosition();
    const int cell_size = sizePx / 8;

    const int column = (event.mouseButton.x - boardPosition.x) / cell_size;
    const int row = (event.mouseButton.y - boardPosition.y) / cell_size;
    auto& clickedPiece = getPiece({row, column});

    DEBUG("[DEBUG] Clicked " + (clickedPiece ? "full" : "empty") + " cell (" +
          S(column) + ", " + S(row) + ")");

    if (!selectedPiece && clickedPiece && clickedPiece->getColor() == turn) {
        DEBUG("[DEBUG] Selecting clicked piece");
        select(clickedPiece);
        return;
    }

    if (!selectedPiece) return;

    for (const auto& move : selectedPiece->getMoves(*this)) {
        if (move.cell == Cell{row, column} &&
            isMoveValid(selectedPiece, move)) {
            auto& otherPiece = getPiece(move.cell);
            DEBUG("[DEBUG] Moving to cell");
            if (otherPiece) {
                DEBUG("[DEBUG] Eating enemy");
            }
            switch (move.type) {
                case Move::Type::Castle:
                    capturableEnPassant = nullptr;
                    break;
                case Move::Type::DoublePawn:
                    DEBUG("[DEBUG] Piece is vulnerable to en passant");
                    capturableEnPassant = selectedPiece;
                    break;
                case Move::Type::EnPassantCapture:
                    capturePiece(capturableEnPassant->getCell());
                    break;
                case Move::Type::Regualar:
                    capturableEnPassant = nullptr;
                    break;
                case Move::Type::ShortCastling:
                    movePiece(getPiece({selectedPiece->getCell().row, 7}),
                              {selectedPiece->getCell().row, 5});
                    break;
                case Move::Type::LongCastling:
                    movePiece(getPiece({selectedPiece->getCell().row, 0}),
                              {selectedPiece->getCell().row, 3});
                    break;
            }
            movePiece(selectedPiece, move.cell);
            unselect();
            advanceTurn();
            checkForChecks(turn);
            return;
        }
    }

    if (clickedPiece && selectedPiece->getColor() == clickedPiece->getColor()) {
        if (selectedPiece == clickedPiece) {
            unselect();
            return;
        }
        DEBUG("[DEBUG] Selecting another piece with the same color");
        select(clickedPiece);
        return;
    }

    DEBUG("[DEBUG] Invalid move, unselecting");
    unselect();
}
