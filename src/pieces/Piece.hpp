#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

class Piece : public sf::Drawable, private sf::Transformable {
public:
    enum class Color { White, Black };
    enum class Type { Pawn };

    Piece(int row, int column, Color color, int size = 50);
    virtual std::vector<sf::Vector2u> getMoves() const = 0;

protected:
    void loadTexture(Type type);
    int row, column;

private:
    sf::Texture texture_;
    sf::VertexArray vertices_;
    const int size;
    const Color color;

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
