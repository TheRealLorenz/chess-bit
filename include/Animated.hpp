#pragma once

#include "SFML/Graphics/Transform.hpp"
#include "SFML/Graphics/Transformable.hpp"

class Animated : private sf::Transformable {
public:
    const sf::Transform& getTransform() const;

    void setPosition(const sf::Vector2f& position);
    void setPositionAnimated(const sf::Vector2f& position, int pxPerSecond);

    void setScale(const sf::Vector2f& factors);
    void setScaleAnimated(const sf::Vector2f& factors, int factorPerSecond);

    void update(int deltaMillis);

private:
    void updatePosition(int deltaMillis);
    void updateScale(int deltaMillis);

    sf::Vector2f targetPosition;
    sf::Vector2f targetScale;
    int speedPerSecond;
    int scaleFactorPerSecond;
};
