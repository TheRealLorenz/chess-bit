#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

#include "../Move.hpp"

class Piece : public sf::Drawable, private sf::Transformable {
public:
    enum class Color { White = 0, Black };
    enum class Type { Pawn = 0, Tower, Knight, Bishop, Queen, King };

    Piece(Cell cell, Color color, bool hasMoved = false, int size = 50);
    virtual std::vector<Move> getMoves(
        const std::vector<std::shared_ptr<Piece>>& pieces) const = 0;
    Cell getCell() const { return {row, column}; };
    void setCell(Cell cell);
    const Color getColor() const { return color; }

protected:
    void loadTexture(Type type);
    int row, column;
    const Color color;
    bool hasMoved;

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
