#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <vector>

#include "../Cell.hpp"

class Piece : public sf::Drawable, private sf::Transformable {
public:
    enum class Color { White, Black };
    enum class Type { Pawn };

    Piece(Cell cell, Color color, int size = 50);
    virtual std::vector<std::vector<Cell>> getMoves() const = 0;
    Cell getCell() const { return {row, column}; };
    void setCell(Cell cell);
    const Color getColor() const { return color; }

protected:
    void loadTexture(Type type);
    uint8_t row, column;
    const Color color;

private:
    sf::Texture texture_;
    sf::VertexArray vertices_;
    const int size;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // apply the entity's transform -- combine it with the one that was
        // passed by the caller
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &texture_;

        // draw the vertex array
        target.draw(vertices_, states);
    }
};
