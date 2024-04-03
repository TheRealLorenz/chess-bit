#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "Board.hpp"
#include "debug.hpp"
#include "pieces/Pawn.hpp"

Board::Board(const int size) : size(size) {
    vertices_.setPrimitiveType(sf::Triangles);
    // Each cell is composed of two triangles
    // hence 3 vertices for triangle
    vertices_.resize(size * size * 6);
    const int cell_size = size / CELL_IN_ROW;

    for (int y = 0; y < CELL_IN_ROW; y++) {
        for (int x = 0; x < CELL_IN_ROW; x++) {
            auto vertices = &vertices_[(x + y * size) * 6];

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

            for (int i = 0; i < 6; i++) {
                if ((x + y) % 2 == 0) {
                    vertices[i].color = sf::Color::White;
                } else {
                    vertices[i].color = sf::Color::Black;
                }
            }
        }
    }

    for (int i = 0; i < CELL_IN_ROW; i++) {
        pieces[i * CELL_IN_ROW + i] =
            new Pawn({i, i}, Piece::Color::Black, cell_size);
    }
}

Board::~Board() {
    for (auto& p : pieces) {
        if (p) delete p;
    }
}

Piece *const Board::getPiece(Cell cell) const {
    return pieces[cell.row * CELL_IN_ROW + cell.column];
}

void Board::resetColors() {
    const int cell_size = size / CELL_IN_ROW;

    for (int y = 0; y < CELL_IN_ROW; y++) {
        for (int x = 0; x < CELL_IN_ROW; x++) {
            auto vertices = &vertices_[(x + y * size) * 6];

            for (int i = 0; i < 6; i++) {
                if ((x + y) % 2 == 0) {
                    vertices[i].color = sf::Color::White;
                } else {
                    vertices[i].color = sf::Color::Black;
                }
            }
        }
    }
}

void Board::highlightMoves() {
    if (!selectedPiece) return;
    auto moves = selectedPiece->getMoves();
    auto cell = selectedPiece->getCell();
    auto vertices = &vertices_[(cell.column + cell.row * size) * 6];

    for (int i = 0; i < 6; i++) {
        vertices[i].color = sf::Color::Yellow;
    }

    for (auto& moveSet : moves) {
        for (auto& cell : moveSet) {
            auto otherPiece = getPiece(cell);
            if (otherPiece &&
                otherPiece->getColor() == selectedPiece->getColor())
                break;

            auto vertices = &vertices_[(cell.column + cell.row * size) * 6];

            for (int i = 0; i < 6; i++) {
                vertices[i].color = sf::Color::Yellow;
            }

            if (otherPiece &&
                otherPiece->getColor() != selectedPiece->getColor())
                break;
        }
    }
}

void Board::select(Piece *p) {
    if (!p) return;

    selectedPiece = p;
    highlightMoves();
}

void Board::unselect() {
    selectedPiece = nullptr;
    resetColors();
}

void Board::move(Piece *p, Cell cell) {
    auto oldCell = p->getCell();
    p->setCell(cell);
    pieces[cell.row * CELL_IN_ROW + cell.column] = p;
    pieces[oldCell.row * CELL_IN_ROW + oldCell.column] = nullptr;
}

void Board::onMouseEvent(const sf::Event& event) {
    const auto boardPosition = getPosition();
    const int cell_size = size / CELL_IN_ROW;

    const int column = (event.mouseButton.x - boardPosition.x) / cell_size;
    const int row = (event.mouseButton.y - boardPosition.y) / cell_size;
    auto clickedPiece = getPiece({row, column});

    DEBUG("[DEBUG] Clicked " << (clickedPiece ? "full" : "empty") << " cell ("
                             << column << ", " << row << ")" << std::endl);

    if (!selectedPiece && clickedPiece) {
        DEBUG("[DEBUG] Selecting clicked piece" << std::endl);
        select(clickedPiece);
        return;
    }

    if (!selectedPiece) return;

    if (clickedPiece && selectedPiece->getColor() == clickedPiece->getColor()) {
        unselect();
        select(clickedPiece);
        return;
    }

    auto moves = selectedPiece->getMoves();

    for (auto& moveSet : moves) {
        for (auto& cell : moveSet) {
            auto otherPiece = getPiece(cell);
            if (otherPiece && cell != Cell{row, column}) break;

            if (!otherPiece && cell == Cell{row, column}) {
                DEBUG("[DEBUG] Moving to empty cell" << std::endl);
                move(selectedPiece, cell);
                unselect();
                return;
            }

            if (cell == Cell{row, column}) {
                DEBUG("[DEBUG] Eating enemy" << std::endl);
                return;
            }
        }
    }

    DEBUG("[DEBUG] Invalid move, unselecting" << std::endl);
    unselect();
}
