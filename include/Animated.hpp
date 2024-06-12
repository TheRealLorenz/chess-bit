#pragma once

#include "AnimatedValue.hpp"
#include "SFML/Graphics/Transform.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/System/Vector2.hpp"

class Animated : private sf::Transformable {
public:
    const sf::Transform& getTransform() const;

    void setPosition(const sf::Vector2f& position,
                     std::chrono::milliseconds duration = 0ms);

    void setScale(const sf::Vector2f& factors,
                  std::chrono::milliseconds duration = 0ms);

    void update(std::chrono::milliseconds duration);

private:
    AnimatedValue<float> x, y;
    AnimatedValue<float> scaleX = 1;
    AnimatedValue<float> scaleY = 1;
};
