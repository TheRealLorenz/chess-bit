#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

#include "pieces/Piece.hpp"

class Board : public sf::Drawable, public sf::Transformable {
public:
    enum class Tile { Light, Dark, Highlight };

    explicit Board(const int size = 400);
    const sf::FloatRect getBounds() const { return baseTiles.getBounds(); }
    void onMouseEvent(const sf::Event& event);

private:
    // Lenght of a side of the board, in pixels.
    // It's a square, so I only need a single value
    const int size;
    static const int CELL_IN_ROW = 8;
    std::shared_ptr<Piece> selectedPiece = nullptr;

    sf::VertexArray baseTiles;
    sf::VertexArray highlightTiles;
    sf::Texture texture_;
    std::vector<std::shared_ptr<Piece>> pieces =
        std::vector<std::shared_ptr<Piece>>(CELL_IN_ROW * CELL_IN_ROW);

    const std::shared_ptr<Piece>& getPiece(Cell cell) const;
    void select(const std::shared_ptr<Piece>& p);
    void unselect();
    void highlightMoves();
    void move(const std::shared_ptr<Piece>& p, Cell cell);
    void populate(const int schema[64][2]);
    void setTile(sf::Vertex *vertices, Tile tile);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // apply the entity's transform -- combine it with the one that was
        // passed by the caller
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &texture_;

        // draw the vertex array
        target.draw(baseTiles, states);
        target.draw(highlightTiles, states);

        for (auto& p : pieces) {
            if (p) target.draw(*p, states);
        }
    }
};
