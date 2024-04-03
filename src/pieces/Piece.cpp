#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>

#include "Piece.hpp"

Piece::Piece(int row, int column, Color color, int size)
    : row(row), column(column), color(color), size(size) {
    vertices_.setPrimitiveType(sf::Triangles);
    vertices_.resize(6);

    vertices_[0].position = sf::Vector2f(0, 0);
    vertices_[1].position = sf::Vector2f(size, 0);
    vertices_[2].position = sf::Vector2f(0, size);
    vertices_[3].position = sf::Vector2f(size, 0);
    vertices_[4].position = sf::Vector2f(0, size);
    vertices_[5].position = sf::Vector2f(size, size);

    setPosition(sf::Vector2f(column * size, row * size));
}

void Piece::loadTexture(Type type) {
    int x = 0;
    int y = 0;
    // Each tile is 42x42 px
    int width = 42;
    int height = 42;

    texture_.loadFromFile("assets/pieces.png");

    switch (type) {
        case Type::Pawn:
            break;
    }

    if (color == Color::White) {
        y += height;
    }

    vertices_[0].texCoords = sf::Vector2f(x, y);
    vertices_[1].texCoords = sf::Vector2f(x + width, y);
    vertices_[2].texCoords = sf::Vector2f(x, y + height);
    vertices_[3].texCoords = sf::Vector2f(x + width, y);
    vertices_[4].texCoords = sf::Vector2f(x, y + height);
    vertices_[5].texCoords = sf::Vector2f(x + width, y + height);
}
