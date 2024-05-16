#pragma once

#include <memory>

#include "Board.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Game {
private:
    std::unique_ptr<sf::RenderWindow> window;
    Board board;

    void on_event(const sf::Event& event);
    void render() const;

public:
    Game();
    int run();
};
