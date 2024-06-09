#pragma once

#include "SFML/Graphics/Transformable.hpp"

class Animatable : public sf::Transformable {
public:
    void setPositionAnimated(const sf::Vector2f& position, int pxPerSecond);
    void update(int deltaMillis);

private:
    float targetX, targetY;
    int speedPerSecond;
};
