#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>

#include "Board.hpp"

Board::Piece::Piece(Cell cell, Color color, bool hasMoved, int sizePx)
    : color(color), sizePx(sizePx) {
    vertices.setPrimitiveType(sf::Triangles);
    vertices.resize(6);

    vertices[0].position = sf::Vector2f(0, 0);
    vertices[1].position = sf::Vector2f(sizePx, 0);
    vertices[2].position = sf::Vector2f(0, sizePx);
    vertices[3].position = sf::Vector2f(sizePx, 0);
    vertices[4].position = sf::Vector2f(0, sizePx);
    vertices[5].position = sf::Vector2f(sizePx, sizePx);

    setCell(cell);
    this->hasMoved = hasMoved;
}

void Board::Piece::loadTexture(Type type) {
    int x = 0;
    int y = 0;
    // Each tile is 42x42 px
    int width = 42;
    int height = 42;

    texture.loadFromFile("assets/pieces.png");

    switch (type) {
        case Type::Pawn:
            break;
        case Type::Tower:
            x += width;
            break;
        case Type::Knight:
            x += 2 * width;
            break;
        case Type::Bishop:
            x += 3 * width;
            break;
        case Type::Queen:
            x += 4 * width;
            break;
        case Type::King:
            x += 5 * width;
            break;
    }

    if (color == Color::White) {
        y += height;
    }

    vertices[0].texCoords = sf::Vector2f(x, y);
    vertices[1].texCoords = sf::Vector2f(x + width, y);
    vertices[2].texCoords = sf::Vector2f(x, y + height);
    vertices[3].texCoords = sf::Vector2f(x + width, y);
    vertices[4].texCoords = sf::Vector2f(x, y + height);
    vertices[5].texCoords = sf::Vector2f(x + width, y + height);
}

void Board::Piece::setCell(Cell cell) {
    row = cell.row;
    column = cell.column;
    hasMoved = true;

    setPosition(sf::Vector2f(column * sizePx, row * sizePx));
}