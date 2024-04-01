#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "Piece.hpp"

class Board : public sf::Drawable, public sf::Transformable {
public:
    Board();

private:
    static const int N_CELL = 8;
    static const int CELL_SIZE = 50;
    sf::VertexArray vertices_;
    sf::Texture texture_;
    std::vector<std::unique_ptr<Piece>> pieces;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // apply the entity's transform -- combine it with the one that was
        // passed by the caller
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &texture_;

        // draw the vertex array
        target.draw(vertices_, states);

        for (auto& p : pieces) {
            target.draw(*p);
        }
    }
};
