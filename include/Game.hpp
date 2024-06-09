#pragma once

#include <cstdint>

#include "Board.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/WindowStyle.hpp"

class Game {
public:
    Game();
    int run();

    struct WindowSettings {
        const char *windowTitle = "Chess Bit";

        uint32_t width = 400;
        uint32_t height = 400;
        uint32_t framerateLimit = 60;
        uint32_t style = sf::Style::Titlebar | sf::Style::Close;
    };

private:
    void on_event(const sf::Event& event);
    void render();

    WindowSettings settings;
    Board board;
    sf::RenderWindow window;
};
