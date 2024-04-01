#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include "Board.hpp"

Board::Board(const int size) : size(size) {
    vertices_.setPrimitiveType(sf::Triangles);
    // Each cell is composed of two triangles
    // hence 3 vertices for triangle
    vertices_.resize(size * size * 6);
    const int cell_size = size / CELL_IN_ROW;

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
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

    for (int i = 0; i < 8; i++) {
        pieces.push_back(std::unique_ptr<Piece>(
            new Piece(i * cell_size, i * cell_size, cell_size)));
    }
}
