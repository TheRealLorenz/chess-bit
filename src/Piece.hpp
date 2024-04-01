#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class Piece : public sf::Drawable, public sf::Transformable {
public:
    Piece(int x, int y);

private:
    sf::Texture texture_;
    sf::VertexArray vertices_;
    static const int SIZE = 50;

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
