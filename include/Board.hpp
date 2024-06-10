#pragma once

#include <memory>
#include <optional>

#include "Color.hpp"
#include "Matrix.hpp"
#include "Move.hpp"
#include "Piece.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Window/Event.hpp"
#include "Tile.hpp"

class Board : public sf::Drawable, public sf::Transformable {
public:
    explicit Board(const int sizePx = 400);
    const sf::FloatRect getBounds() const;
    void onClick(const sf::Event& event);
    const std::shared_ptr<Piece>& getPiece(Cell cell) const;
    const std::shared_ptr<Piece>& getCapturableEnPassant() const {
        return capturableEnPassant;
    }
    bool isUnderAttack(Cell cell, Color by) const;
    void capturePiece(Cell cell);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    // Lenght of a side of the board, in pixels.
    // It's a square, so I only need a single value
    const int sizePx;
    Color turn = Color::White;

    std::shared_ptr<Piece> selectedPiece = nullptr;
    std::shared_ptr<Piece> capturableEnPassant = nullptr;
    std::shared_ptr<Piece> whiteKing = nullptr;
    std::shared_ptr<Piece> blackKing = nullptr;
    Matrix<std::shared_ptr<Piece>, 8> pieces;

    Tile baseTiles[8 * 8];
    std::vector<Tile> highlightTiles{8 * 8};
    std::optional<Tile> checkTile;

    void select(const std::shared_ptr<Piece>& p);
    void unselect();
    void highlightMoves();
    void movePiece(const std::shared_ptr<Piece>& p, Cell cell);
    void populate(const int schema[64][2]);
    void checkForChecks();
    void setCheckCell(Cell cell);
    bool isMoveValid(const std::shared_ptr<Piece>& piece, Move move) const;
    void advanceTurn();
};
