#include "Animatable.hpp"

void Animatable::setPositionAnimated(const sf::Vector2f& position,
                                     int pxPerSecond) {
    targetX = position.x;
    targetY = position.y;
    speedPerSecond = pxPerSecond;
}

void Animatable::update(int deltaMillis) {
    auto position = getPosition();
    if (position.x == targetX && position.y == targetY) {
        return;
    }

    if (position.x < targetX) {
        position.x = std::min(
            position.x + (float)speedPerSecond * deltaMillis / 1000, targetX);
    } else if (position.x > targetX) {
        position.x = std::max(
            position.x - (float)speedPerSecond * deltaMillis / 1000, targetX);
    }

    if (position.y < targetY) {
        position.y = std::min(
            position.y + (float)speedPerSecond * deltaMillis / 1000, targetY);
    } else if (position.y > targetY) {
        position.y = std::max(
            position.y - (float)speedPerSecond * deltaMillis / 1000, targetY);
    }

    setPosition(position);
}
