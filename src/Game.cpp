#include "Game.hpp"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "debug.hpp"

Game::Game()
    : board(Board(std::min(settings.width, settings.height))),
      window(sf::RenderWindow({settings.width, settings.height},
                              settings.windowTitle, settings.style)) {
    window.setFramerateLimit(60);
}

void Game::on_event(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::Closed: {
            window.close();
            break;
        }
        case sf::Event::MouseButtonPressed: {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (board.getBounds().contains(sf::Vector2f(
                        event.mouseButton.x, event.mouseButton.y))) {
                    board.onClick(event);
                }
                break;
            }
            DEBUG("[TRACE] Unhandled mouse button: " +
                  S(event.mouseButton.button));
            break;
        }
        default: {
            if (event.type != sf::Event::EventType::MouseMoved)
                DEBUG("[TRACE] Unhandled event type: " + S(event.type));
            break;
        }
    }
}

void Game::render() {
    window.clear();
    window.draw(board);
    window.display();
}

int Game::run() {
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Time delta = deltaClock.restart();

        for (auto event = sf::Event{}; window.pollEvent(event);) {
            on_event(event);
        }
        board.update(delta.asMilliseconds());
        render();
    }

    return 0;
}
