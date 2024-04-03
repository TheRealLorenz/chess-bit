#include "Pawn.hpp"

Pawn::Pawn(int row, int column, Color color, const int size)
    : Piece(row, column, color, size) {
    loadTexture(Type::Pawn);
}

std::vector<sf::Vector2u> Pawn::getMoves() const {
    return std::vector<sf::Vector2u>();
}
