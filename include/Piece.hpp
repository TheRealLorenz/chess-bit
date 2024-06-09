#pragma once

#include "Animatable.hpp"
#include "Color.hpp"
#include "Move.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/VertexArray.hpp"

class Board;

class Piece : public sf::Drawable, private Animatable {
public:
    enum class Type { Pawn = 0, Tower, Knight, Bishop, Queen, King };

    Piece(Cell cell, Color color, bool hasMoved = false, int sizePx = 50);

    virtual std::vector<Move> getMoves(const Board& board) const = 0;
    Cell getCell() const { return {row, column}; };
    void setCell(Cell cell, int animationSpeed = 0);
    const Color getColor() const { return color; }
    bool hasMoved() const { return moved; }
    void setMoved(bool moved) { Piece::moved = moved; }
    void update(int deltaMillis) { Animatable::update(deltaMillis); }

protected:
    void loadTexture(Type type);
    int row, column;
    const Color color;
    bool moved;

private:
    sf::Texture texture;
    sf::VertexArray vertices;
    const int sizePx;
    // Scaling factor to apply to the piece.
    // A scaling factor of 1 makes the piece as big
    // as the cell itself.
    static constexpr float scaleFactor = 0.8;
    const float delta = sizePx * (1 - scaleFactor) / 2;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // apply the entity's transform -- combine it with the one that was
        // passed by the caller
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &texture;

        // draw the vertex array
        target.draw(vertices, states);
    }
};
