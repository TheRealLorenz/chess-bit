#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

#include "Board.hpp"
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
    texture.loadFromFile("assets/tiles.png");
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

void Board::populate(const int schema[64][2]) {
    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 8; column++) {
            if (schema[row * 8 + column][0] == -1) continue;

            auto type = Piece::Type(schema[row * 8 + column][0]);
            auto color = Piece::Color(schema[row * 8 + column][1]);

            switch (type) {
                case Piece::Type::Pawn:
                    pieces[row * 8 + column] =
                        std::shared_ptr<Piece>(new Pawn({row, column}, color));
                    break;
                case Piece::Type::Tower:
                    pieces[row * 8 + column] =
                        std::shared_ptr<Piece>(new Tower({row, column}, color));
                    break;
                case Piece::Type::Knight:
                    pieces[row * 8 + column] = std::shared_ptr<Piece>(
                        new Knight({row, column}, color));
                    break;
                case Piece::Type::Bishop:
                    pieces[row * 8 + column] = std::shared_ptr<Piece>(
                        new Bishop({row, column}, color));
                    break;
                case Piece::Type::Queen:
                    pieces[row * 8 + column] =
                        std::shared_ptr<Piece>(new Queen({row, column}, color));
                    break;
                case Piece::Type::King:
                    pieces[row * 8 + column] =
                        std::shared_ptr<Piece>(new King({row, column}, color));
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

const std::shared_ptr<Board::Piece>& Board::getPiece(Cell cell) const {
    return pieces[cell.row * 8 + cell.column];
}

void Board::capturePiece(Cell cell) {
    pieces[cell.row * 8 + cell.column] = nullptr;
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
        auto vertices = &baseTiles[(move.cell.column + move.cell.row * 8) * 6];

        for (int i = 0; i < 6; i++) {
            highlightTiles.append(sf::Vertex(vertices[i].position));
        }
        setTile(&highlightTiles[tile * 6], Tile::Highlight);
        tile++;
    }
}

bool Board::isCellUnderAttack(Cell cell, Board::Piece::Color by) {
    for (auto& p : pieces) {
        if (!p) continue;

        if (p->getColor() == by) {
            for (auto& move : p->getMoves(*this)) {
                if (move.cell == cell) {
                    return true;
                }
            }
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
    std::shared_ptr<Piece> whiteKing = nullptr;
    std::shared_ptr<Piece> blackKing = nullptr;

    for (auto& p : pieces) {
        if (p && std::dynamic_pointer_cast<King>(p)) {
            if (p->getColor() == Board::Piece::Color::White) {
                whiteKing = p;
            } else {
                blackKing = p;
            }
        }
    }

    checkTiles.clear();
    if (isCellUnderAttack(blackKing->getCell(), Board::Piece::Color::White)) {
        DEBUG("[DEBUG] Black King is under attack" << std::endl);
        setCheckCell(blackKing->getCell());
    } else if (isCellUnderAttack(whiteKing->getCell(),
                                 Board::Piece::Color::Black)) {
        DEBUG("[DEBUG] White King is under attack" << std::endl);
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
    pieces[cell.row * 8 + cell.column] =
        std::move(pieces[oldCell.row * 8 + oldCell.column]);
}

void Board::onClick(const sf::Event& event) {
    const auto boardPosition = getPosition();
    const int cell_size = sizePx / 8;

    const int column = (event.mouseButton.x - boardPosition.x) / cell_size;
    const int row = (event.mouseButton.y - boardPosition.y) / cell_size;
    auto& clickedPiece = getPiece({row, column});

    DEBUG("[DEBUG] Clicked " << (clickedPiece ? "full" : "empty") << " cell ("
                             << column << ", " << row << ")" << std::endl);

    if (!selectedPiece && clickedPiece) {
        DEBUG("[DEBUG] Selecting clicked piece" << std::endl);
        select(clickedPiece);
        return;
    }

    if (!selectedPiece) return;

    if (clickedPiece && selectedPiece->getColor() == clickedPiece->getColor()) {
        if (selectedPiece == clickedPiece) {
            unselect();
            return;
        }
        DEBUG("[DEBUG] Selecting another piece with the same color"
              << std::endl);
        select(clickedPiece);
        return;
    }

    auto moves = selectedPiece->getMoves(*this);

    for (auto& move : moves) {
        if (move.cell == Cell{row, column}) {
            auto& otherPiece = getPiece(move.cell);
            DEBUG("[DEBUG] Moving to cell" << std::endl);
            if (otherPiece) {
                DEBUG("[DEBUG] Eating enemy" << std::endl);
            }
            switch (move.type) {
                case Move::Type::Castle:
                    capturableEnPassant = nullptr;
                    break;
                case Move::Type::DoublePawn:
                    DEBUG("[DEBUG] Piece is vulnerable to en passant"
                          << std::endl);
                    capturableEnPassant = selectedPiece;
                    break;
                case Move::Type::EnPassantCapture:
                    capturePiece(capturableEnPassant->getCell());
                    break;
                case Move::Type::Regualar:
                    capturableEnPassant = nullptr;
                    break;
            }
            movePiece(selectedPiece, move.cell);
            unselect();
            checkForChecks();
            return;
        }
    }

    DEBUG("[DEBUG] Invalid move, unselecting" << std::endl);
    unselect();
}
