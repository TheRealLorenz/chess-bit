#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <memory>

#include "Piece.hpp"

class Board : public sf::Drawable, public sf::Transformable {
public:
    explicit Board(const int size = 400);

private:
    // Lenght of a side of the board, in pixels.
    // It's a square, so I only need a single value
    const int size;
    static const int CELL_IN_ROW = 8;

    sf::VertexArray vertices_;
    sf::Texture texture_;
    std::vector<std::unique_ptr<Piece>> pieces;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // apply the entity's transform -- combine it with the one that was
        // passed by the caller
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &texture_;

        // draw the vertex array
        target.draw(vertices_, states);

        for (auto& p : pieces) {
            target.draw(*p, states);
        }
    }
};
