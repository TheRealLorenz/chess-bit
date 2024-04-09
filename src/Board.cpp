#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

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

Board::Board(const int size) : size(size) {
    baseTiles.setPrimitiveType(sf::Triangles);
    highlightTiles.setPrimitiveType(sf::Triangles);
    // Each cell is composed of two triangles
    // hence 3 vertices for triangle
    texture_.loadFromFile("assets/tiles.png");
    baseTiles.resize(size * size * 6);
    const int cell_size = size / CELL_IN_ROW;

    for (int y = 0; y < CELL_IN_ROW; y++) {
        for (int x = 0; x < CELL_IN_ROW; x++) {
            auto vertices = &baseTiles[(x + y * size) * 6];

            // Upper left triangle
            vertices[0].position = sf::Vector2f(x * cell_size, y * cell_size);
            vertices[1].position =
                sf::Vector2f((x + 1) * cell_size, y * cell_size);
            vertices[2].position =
                sf::Vector2f(x * cell_size, (y + 1) * cell_size);

            // Bottom right triangle
            vertices[3].position =
                sf::Vector2f((x + 1) * cell_size, y * cell_size);
            vertices[4].position =
                sf::Vector2f(x * cell_size, (y + 1) * cell_size);
            vertices[5].position =
                sf::Vector2f((x + 1) * cell_size, (y + 1) * cell_size);

            setTile(vertices, (x + y) % 2 == 0 ? Tile::Light : Tile::Dark);
        }
    }

    populate(defaultSchema);
}

void Board::populate(const int schema[64][2]) {
    for (int row = 0; row < CELL_IN_ROW; row++) {
        for (int column = 0; column < CELL_IN_ROW; column++) {
            if (schema[row * CELL_IN_ROW + column][0] == -1) continue;

            auto type = Piece::Type(schema[row * CELL_IN_ROW + column][0]);
            auto color = Piece::Color(schema[row * CELL_IN_ROW + column][1]);

            switch (type) {
                case Piece::Type::Pawn:
                    pieces[row * CELL_IN_ROW + column] =
                        std::shared_ptr<Piece>(new Pawn({row, column}, color));
                    break;
                case Piece::Type::Tower:
                    pieces[row * CELL_IN_ROW + column] =
                        std::shared_ptr<Piece>(new Tower({row, column}, color));
                    break;
                case Piece::Type::Knight:
                    pieces[row * CELL_IN_ROW + column] = std::shared_ptr<Piece>(
                        new Knight({row, column}, color));
                    break;
                case Piece::Type::Bishop:
                    pieces[row * CELL_IN_ROW + column] = std::shared_ptr<Piece>(
                        new Bishop({row, column}, color));
                    break;
                case Piece::Type::Queen:
                    pieces[row * CELL_IN_ROW + column] =
                        std::shared_ptr<Piece>(new Queen({row, column}, color));
                    break;
                case Piece::Type::King:
                    pieces[row * CELL_IN_ROW + column] =
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
    }

    vertices[0].texCoords = sf::Vector2f(x, y);
    vertices[1].texCoords = sf::Vector2f(x + width, y);
    vertices[2].texCoords = sf::Vector2f(x, y + height);
    vertices[3].texCoords = sf::Vector2f(x + width, y);
    vertices[4].texCoords = sf::Vector2f(x, y + height);
    vertices[5].texCoords = sf::Vector2f(x + width, y + height);
}

const std::shared_ptr<Piece>& Board::getPiece(Cell cell) const {
    return pieces[cell.row * CELL_IN_ROW + cell.column];
}

void Board::highlightMoves() {
    if (!selectedPiece) return;
    highlightTiles.clear();

    auto moves = selectedPiece->getMoves(pieces);
    auto cell = selectedPiece->getCell();
    auto vertices = &baseTiles[(cell.column + cell.row * size) * 6];

    for (int i = 0; i < 6; i++) {
        highlightTiles.append(sf::Vertex(vertices[i].position));
    }
    setTile(&highlightTiles[0], Tile::Highlight);

    int tile = 1;
    for (auto& move : moves) {
        auto vertices =
            &baseTiles[(move.cell.column + move.cell.row * size) * 6];

        for (int i = 0; i < 6; i++) {
            highlightTiles.append(sf::Vertex(vertices[i].position));
        }
        setTile(&highlightTiles[tile * 6], Tile::Highlight);
        tile++;
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
    pieces[cell.row * CELL_IN_ROW + cell.column] =
        std::move(pieces[oldCell.row * CELL_IN_ROW + oldCell.column]);
}

void Board::onMouseEvent(const sf::Event& event) {
    const auto boardPosition = getPosition();
    const int cell_size = size / CELL_IN_ROW;

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

    auto moves = selectedPiece->getMoves(pieces);

    for (auto& move : moves) {
        if (move.cell == Cell{row, column}) {
            auto& otherPiece = getPiece(move.cell);
            DEBUG("[DEBUG] Moving to cell" << std::endl);
            if (otherPiece) {
                DEBUG("[DEBUG] Eating enemy" << std::endl);
            }
            movePiece(selectedPiece, move.cell);
            unselect();
            return;
        }
    }

    DEBUG("[DEBUG] Invalid move, unselecting" << std::endl);
    unselect();
}
