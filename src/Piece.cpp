#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>

#include "Piece.hpp"

Piece::Piece(int x, int y, int size) : size(size) {
    vertices_.setPrimitiveType(sf::Triangles);
    vertices_.resize(6);

    vertices_[0].position = sf::Vector2f(0, 0);
    vertices_[1].position = sf::Vector2f(size, 0);
    vertices_[2].position = sf::Vector2f(0, size);
    vertices_[3].position = sf::Vector2f(size, 0);
    vertices_[4].position = sf::Vector2f(0, size);
    vertices_[5].position = sf::Vector2f(size, size);

    for (int i = 0; i < 6; i++) {
        vertices_[i].color = sf::Color::Yellow;
    }

    setPosition(sf::Vector2f(x, y));
}
