#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>

#include "pieces/Piece.hpp"

class Board : public sf::Drawable, public sf::Transformable {
public:
    explicit Board(const int size = 400);
    ~Board();
    const sf::FloatRect getBounds() const { return vertices_.getBounds(); }
    void onMouseEvent(const sf::Event& event);

private:
    // Lenght of a side of the board, in pixels.
    // It's a square, so I only need a single value
    const int size;
    static const int CELL_IN_ROW = 8;
    Piece *selectedPiece = nullptr;

    sf::VertexArray vertices_;
    sf::Texture texture_;
    // Init array to nullptrs
    Piece *pieces[CELL_IN_ROW * CELL_IN_ROW] = {};

    Piece *const getPiece(Cell cell) const;
    void select(Piece *p);
    void unselect();
    void resetColors();
    void highlightMoves();
    void move(Piece *p, Cell cell);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // apply the entity's transform -- combine it with the one that was
        // passed by the caller
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &texture_;

        // draw the vertex array
        target.draw(vertices_, states);

        for (Piece *p : pieces) {
            if (p) target.draw(*p, states);
        }
    }
};
