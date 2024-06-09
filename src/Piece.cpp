#include "Board.hpp"
#include "ResourceManager.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/System/Vector2.hpp"

Piece::Piece(Cell cell, Color color, bool hasMoved, int sizePx)
    : color(color), sizePx(sizePx) {
    vertices.setPrimitiveType(sf::Triangles);
    vertices.resize(6);

    vertices[0].position = sf::Vector2f(0, 0);
    vertices[1].position = sf::Vector2f(sizePx * scaleFactor, 0);
    vertices[2].position = sf::Vector2f(0, sizePx * scaleFactor);
    vertices[3].position = sf::Vector2f(sizePx * scaleFactor, 0);
    vertices[4].position = sf::Vector2f(0, sizePx * scaleFactor);
    vertices[5].position =
        sf::Vector2f(sizePx * scaleFactor, sizePx * scaleFactor);

    setCell(cell);
    Piece::moved = hasMoved;
}

void Piece::loadTexture(Type type) {
    int x = 0;
    int y = 0;
    // Each tile is 42x42 px
    int width = 42;
    int height = 42;

    texture = ResourceManager::get().texture("pieces.png");

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

void Piece::setCell(Cell cell) {
    row = cell.row;
    column = cell.column;
    moved = true;
    const float delta = sizePx * (1 - scaleFactor) / 2;

    setPosition(sf::Vector2f(column * sizePx + delta, row * sizePx + delta));
}
