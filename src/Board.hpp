#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

#include "Move.hpp"

class Board : public sf::Drawable, public sf::Transformable {
public:
    class Piece : public sf::Drawable, private sf::Transformable {
    public:
        enum class Color { White = 0, Black };
        enum class Type { Pawn = 0, Tower, Knight, Bishop, Queen, King };

        Piece(Cell cell, Color color, bool hasMoved = false, int sizePx = 50);

        virtual std::vector<Move> getMoves(const Board& board) const = 0;
        Cell getCell() const { return {row, column}; };
        void setCell(Cell cell);
        const Color getColor() const { return color; }
        bool hasMoved() const { return moved; }
        void setMoved(bool moved) { Piece::moved = moved; }

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

        virtual void draw(sf::RenderTarget& target,
                          sf::RenderStates states) const {
            // apply the entity's transform -- combine it with the one that was
            // passed by the caller
            states.transform *= getTransform();

            // apply the tileset texture
            states.texture = &texture;

            // draw the vertex array
            target.draw(vertices, states);
        }
    };

    enum class Tile { Light, Dark, Highlight, Check };

    explicit Board(const int sizePx = 400);
    const sf::FloatRect getBounds() const { return baseTiles.getBounds(); }
    void onClick(const sf::Event& event);
    const std::shared_ptr<Piece>& getPiece(Cell cell) const;
    const std::shared_ptr<Piece>& getCapturableEnPassant() const {
        return capturableEnPassant;
    }
    bool isUnderAttack(Cell cell, Piece::Color by) const;
    void capturePiece(Cell cell);

private:
    // Lenght of a side of the board, in pixels.
    // It's a square, so I only need a single value
    const int sizePx;

    std::shared_ptr<Piece> selectedPiece = nullptr;
    std::shared_ptr<Piece> capturableEnPassant = nullptr;
    std::shared_ptr<Piece> whiteKing = nullptr;
    std::shared_ptr<Piece> blackKing = nullptr;
    std::vector<std::shared_ptr<Piece>> pieces{8 * 8};

    sf::VertexArray baseTiles;
    sf::VertexArray highlightTiles;
    sf::VertexArray checkTiles;
    sf::Texture texture;

    void select(const std::shared_ptr<Piece>& p);
    void unselect();
    void highlightMoves();
    void movePiece(const std::shared_ptr<Piece>& p, Cell cell);
    void populate(const int schema[64][2]);
    void setTile(sf::Vertex *vertices, Tile tile);
    void checkForChecks();
    void setCheckCell(Cell cell);
    bool isMoveValid(Move move) const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // apply the entity's transform -- combine it with the one that was
        // passed by the caller
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &texture;

        // draw the vertex array
        target.draw(baseTiles, states);
        target.draw(highlightTiles, states);
        target.draw(checkTiles, states);

        // draw the pieces
        for (auto& p : pieces) {
            if (p) target.draw(*p, states);
        }
    }
};
