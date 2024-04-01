#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include "Board.hpp"

Board::Board() {
    vertices_.setPrimitiveType(sf::Triangles);
    // Each cell is composed of two triangles
    // hence 3 vertices for triangle
    vertices_.resize(N_CELL * N_CELL * 6);

    for (int y = 0; y < N_CELL; y++) {
        for (int x = 0; x < N_CELL; x++) {
            auto vertices = &vertices_[(x + y * N_CELL) * 6];

            // Upper left triangle
            vertices[0].position = sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE);
            vertices[1].position =
                sf::Vector2f((x + 1) * CELL_SIZE, y * CELL_SIZE);
            vertices[2].position =
                sf::Vector2f(x * CELL_SIZE, (y + 1) * CELL_SIZE);

            // Bottom right triangle
            vertices[3].position =
                sf::Vector2f((x + 1) * CELL_SIZE, y * CELL_SIZE);
            vertices[4].position =
                sf::Vector2f(x * CELL_SIZE, (y + 1) * CELL_SIZE);
            vertices[5].position =
                sf::Vector2f((x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);

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
        pieces.push_back(
            std::unique_ptr<Piece>(new Piece(i * CELL_SIZE, i * CELL_SIZE)));
    }
}
