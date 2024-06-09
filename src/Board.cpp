#include "Board.hpp"

#include <algorithm>
#include <memory>

#include "ResourceManager.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Vertex.hpp"
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
    baseTiles.setPrimitiveType(sf::Triangles);
    highlightTiles.setPrimitiveType(sf::Triangles);
    checkTiles.setPrimitiveType(sf::Triangles);
    // Each cell is composed of two triangles
    // hence 3 vertices for triangle
    texture = ResourceManager::get().texture("tiles.png");
    baseTiles.resize(8 * 8 * 6);
    const int cellSize = sizePx / 8;

    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 8; column++) {
            auto vertices = &baseTiles[(row * 8 + column) * 6];

            // Upper left triangle
            vertices[0].position =
                sf::Vector2f(column * cellSize, row * cellSize);
            vertices[1].position =
                sf::Vector2f((column + 1) * cellSize, row * cellSize);
            vertices[2].position =
                sf::Vector2f(column * cellSize, (row + 1) * cellSize);

            // Bottom right triangle
            vertices[3].position =
                sf::Vector2f((column + 1) * cellSize, row * cellSize);
            vertices[4].position =
                sf::Vector2f(column * cellSize, (row + 1) * cellSize);
            vertices[5].position =
                sf::Vector2f((column + 1) * cellSize, (row + 1) * cellSize);

            setTile(vertices,
                    (column + row) % 2 == 0 ? Tile::Light : Tile::Dark);
        }
    }

    populate(defaultSchema);
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the entity's transform -- combine it with the one that was
    // passed by the caller
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &texture;

    // draw the vertex array
    target.draw(baseTiles, states);
    target.draw(highlightTiles, states);
    target.draw(checkTiles, states);

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

void Board::setTile(sf::Vertex *vertices, Tile tile) {
    int x = 0;
    int y = 0;
    int width = 64;
    int height = 64;

    switch (tile) {
        case Tile::Highlight:
            break;
        case Tile::Dark:
            x += width;
            break;
        case Tile::Light:
            x += 2 * width;
            break;
        case Tile::Check:
            x += 3 * width;
            break;
    }

    vertices[0].texCoords = sf::Vector2f(x, y);
    vertices[1].texCoords = sf::Vector2f(x + width, y);
    vertices[2].texCoords = sf::Vector2f(x, y + height);
    vertices[3].texCoords = sf::Vector2f(x + width, y);
    vertices[4].texCoords = sf::Vector2f(x, y + height);
    vertices[5].texCoords = sf::Vector2f(x + width, y + height);
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

    auto moves = selectedPiece->getMoves(*this);
    auto cell = selectedPiece->getCell();
    auto vertices = &baseTiles[(cell.column + cell.row * 8) * 6];

    for (int i = 0; i < 6; i++) {
        highlightTiles.append(sf::Vertex(vertices[i].position));
    }
    setTile(&highlightTiles[0], Tile::Highlight);

    int tile = 1;
    for (auto& move : moves) {
        if (!isMoveValid(move)) continue;

        vertices = &baseTiles[(move.cell.column + move.cell.row * 8) * 6];

        for (int i = 0; i < 6; i++) {
            highlightTiles.append(sf::Vertex(vertices[i].position));
        }
        setTile(&highlightTiles[tile * 6], Tile::Highlight);
        tile++;
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
    auto tile = &baseTiles[(cell.row * 8 + cell.column) * 6];

    for (int i = 0; i < 6; i++) {
        checkTiles.append(sf::Vertex(tile[i].position));
    }
    setTile(&checkTiles[0], Tile::Check);
}

void Board::checkForChecks() {
    checkTiles.clear();
    if (turn == Color::Black &&
        isUnderAttack(blackKing->getCell(), Color::White)) {
        DEBUG("[DEBUG] Black King is under attack");
        setCheckCell(blackKing->getCell());
    } else if (turn == Color::White &&
               isUnderAttack(whiteKing->getCell(), Color::Black)) {
        DEBUG("[DEBUG] White King is under attack");
        setCheckCell(whiteKing->getCell());
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

bool Board::isMoveValid(Move move) const {
    Board testBoard = Board(*this);
    Cell oldCell = selectedPiece->getCell();
    bool hasMoved = selectedPiece->hasMoved();

    // Using a shallow copy of the Baord to check for
    // checks.
    // The copy constructor performs a copy of the
    // shared pointers, so it shouldn't be costly, but
    // we need to be careful cause it can still edit the
    // original pieces.
    testBoard.movePiece(testBoard.selectedPiece, move.cell);
    bool isValid = false;

    switch (selectedPiece->getColor()) {
        case Color::Black:
            isValid = !testBoard.isUnderAttack(testBoard.blackKing->getCell(),
                                               Color::White);
            break;
        case Color::White:
            isValid = !testBoard.isUnderAttack(testBoard.whiteKing->getCell(),
                                               Color::Black);
            break;
    }

    // Reset selectedPiece
    selectedPiece->setCell(oldCell);
    selectedPiece->setMoved(hasMoved);
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
        if (move.cell == Cell{row, column} && isMoveValid(move)) {
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
            checkForChecks();
            advanceTurn();
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
