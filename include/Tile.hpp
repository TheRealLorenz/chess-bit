#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/Vertex.hpp"

class Tile : public sf::Drawable, public sf::Transformable {
public:
    enum class Type { Light, Dark, Highlight, Check };

    Tile() {}
    Tile(const sf::Vector2f& position, const sf::Vector2f& size, Type type);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Vertex vertices[6];
    sf::Texture texture;

    static const int TILE_SIZE = 16;
};
