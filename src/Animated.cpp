#include "Animated.hpp"

#include <chrono>
#include <cstdlib>

#include "SFML/Graphics/Transformable.hpp"

using namespace std::literals;

const sf::Transform& Animated::getTransform() const {
    return sf::Transformable::getTransform();
}

void Animated::setPosition(const sf::Vector2f& position,
                           std::chrono::milliseconds duration) {
    if (duration == 0ms) {
        x = AnimatedValue(position.x);
        y = AnimatedValue(position.y);
        return;
    }
    x = AnimatedValue(x.get(), position.x, duration);
    y = AnimatedValue(y.get(), position.y, duration);
}

void Animated::setScale(const sf::Vector2f& factors,
                        std::chrono::milliseconds duration) {
    if (duration == 0ms) {
        scaleX = AnimatedValue(factors.x);
        scaleY = AnimatedValue(factors.y);
        return;
    }
    x = AnimatedValue(scaleX.get(), factors.x, duration);
    y = AnimatedValue(scaleY.get(), factors.y, duration);
}

void Animated::update(std::chrono::milliseconds deltaTime) {
    x.update(deltaTime);
    y.update(deltaTime);
    Transformable::setPosition(x.get(), y.get());

    scaleX.update(deltaTime);
    scaleY.update(deltaTime);
    Transformable::setScale(scaleX.get(), scaleY.get());
}
