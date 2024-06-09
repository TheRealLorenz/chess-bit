#include "Animated.hpp"

#include <cmath>
#include <cstdlib>

const sf::Transform& Animated::getTransform() const {
    return sf::Transformable::getTransform();
}

void Animated::setPosition(const sf::Vector2f& position) {
    targetPosition = position;
    sf::Transformable::setPosition(position);
}

void Animated::setPositionAnimated(const sf::Vector2f& position,
                                   int pxPerSecond) {
    targetPosition = position;
    speedPerSecond = pxPerSecond;
}

void Animated::updatePosition(int deltaMillis) {
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

void Animated::setScale(const sf::Vector2f& factors) {
    targetScale = factors;
    sf::Transformable::setScale(factors);
}

void Animated::setScaleAnimated(const sf::Vector2f& factors,
                                int factorPerSecond) {
    targetScale = factors;
    scaleFactorPerSecond = factorPerSecond;
}

void Animated::updateScale(int deltaMillis) {
    auto scale = getScale();
    if (scale == targetScale) {
        return;
    }

    sf::Vector2f delta = targetScale - scale;
    float modulo = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    delta.x /= modulo;
    delta.y /= modulo;

    if (delta.x > 0) {
        scale.x = std::min(scale.x + (float)scaleFactorPerSecond * delta.x *
                                         deltaMillis / 1000,
                           targetScale.x);
    } else if (delta.x < 0) {
        scale.x = std::max(scale.x + (float)scaleFactorPerSecond * delta.x *
                                         deltaMillis / 1000,
                           targetScale.x);
    }

    if (delta.y > 0) {
        scale.y = std::min(scale.y + (float)scaleFactorPerSecond * delta.y *
                                         deltaMillis / 1000,
                           targetScale.y);
    } else if (delta.y < 0) {
        scale.y = std::max(scale.y + (float)scaleFactorPerSecond * delta.y *
                                         deltaMillis / 1000,
                           targetScale.y);
    }

    sf::Transformable::setScale(scale);
}

void Animated::update(int deltaMillis) {
    updatePosition(deltaMillis);
    updateScale(deltaMillis);
}
