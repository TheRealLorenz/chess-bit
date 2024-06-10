#include "Tile.hpp"

#include "ResourceManager.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

Tile::Tile(const sf::Vector2f& position, const sf::Vector2f& size, Type type) {
    texture = ResourceManager::get().texture("textures/tiles.png");

    vertices[0].position = {position.x, position.y};
    vertices[1].position = {position.x + size.x, position.y};
    vertices[2].position = {position.x, position.y + size.y};
    vertices[3].position = {position.x + size.x, position.y};
    vertices[4].position = {position.x, position.y + size.y};
    vertices[5].position = {position.x + size.x, position.y + size.y};

    int textureX = 0;
    int textureY = 0;

    switch (type) {
        case Type::Highlight:
            break;
        case Type::Dark:
            textureX += TILE_SIZE;
            break;
        case Type::Light:
            textureX += 2 * TILE_SIZE;
            break;
        case Type::Check:
            textureX += 3 * TILE_SIZE;
            break;
    }

    vertices[0].texCoords = sf::Vector2f(textureX, textureY);
    vertices[1].texCoords = sf::Vector2f(textureX + TILE_SIZE, textureY);
    vertices[2].texCoords = sf::Vector2f(textureX, textureY + TILE_SIZE);
    vertices[3].texCoords = sf::Vector2f(textureX + TILE_SIZE, textureY);
    vertices[4].texCoords = sf::Vector2f(textureX, textureY + TILE_SIZE);
    vertices[5].texCoords =
        sf::Vector2f(textureX + TILE_SIZE, textureY + TILE_SIZE);
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the entity's transform -- combine it with the one that was
    // passed by the caller
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &texture;

    target.draw(vertices, 6, sf::Triangles, states);
}
