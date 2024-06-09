#include "Animatable.hpp"

#include <cmath>
#include <cstdlib>

const sf::Transform& Animatable::getTransform() const {
    return sf::Transformable::getTransform();
}

void Animatable::setPosition(const sf::Vector2f& position) {
    targetPosition = position;
    sf::Transformable::setPosition(position);
}

void Animatable::setPositionAnimated(const sf::Vector2f& position,
                                     int pxPerSecond) {
    targetPosition = position;
    speedPerSecond = pxPerSecond;
}

void Animatable::updatePosition(int deltaMillis) {
    auto position = getPosition();
    if (position == targetPosition) {
        return;
    }

    sf::Vector2f delta = targetPosition - position;
    float modulo = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    delta.x /= modulo;
    delta.y /= modulo;

    if (delta.x > 0) {
        position.x = std::min(
            position.x + (float)speedPerSecond * delta.x * deltaMillis / 1000,
            targetPosition.x);
    } else if (delta.x < 0) {
        position.x = std::max(
            position.x + (float)speedPerSecond * delta.x * deltaMillis / 1000,
            targetPosition.x);
    }

    if (delta.y > 0) {
        position.y = std::min(
            position.y + (float)speedPerSecond * delta.y * deltaMillis / 1000,
            targetPosition.y);
    } else if (delta.y < 0) {
        position.y = std::max(
            position.y + (float)speedPerSecond * delta.y * deltaMillis / 1000,
            targetPosition.y);
    }

    sf::Transformable::setPosition(position);
}

void Animatable::update(int deltaMillis) {
    updatePosition(deltaMillis);
}
