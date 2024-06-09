#pragma once

#include "SFML/Graphics/Transform.hpp"
#include "SFML/Graphics/Transformable.hpp"

class Animated : private sf::Transformable {
public:
    const sf::Transform& getTransform() const;

    void setPosition(const sf::Vector2f& position);
    void setPositionAnimated(const sf::Vector2f& position, int pxPerSecond);

    void update(int deltaMillis);

private:
    void updatePosition(int deltaMillis);

    sf::Vector2f targetPosition;
    int speedPerSecond;
};
