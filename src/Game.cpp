#include <memory>

#include "Game.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Mouse.hpp"
#include "debug.hpp"

Game::Game() {
    window = std::unique_ptr<sf::RenderWindow>(
        new sf::RenderWindow{{800u, 600u}, "Chess Bit"});
    window->setFramerateLimit(60);
}

void Game::on_event(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::Closed: {
            window->close();
            break;
        }
        case sf::Event::Resized: {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0.f, 0.f, event.size.width,
                                      event.size.height);
            window->setView(sf::View(visibleArea));
            break;
        }
        case sf::Event::MouseButtonPressed: {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (board.getBounds().contains(sf::Vector2f(
                        event.mouseButton.x, event.mouseButton.y))) {
                    board.onMouseEvent(event);
                }
                break;
            }
            DEBUG("[TRACE] Unhandled mouse button: " << event.mouseButton.button
                                                     << std::endl);
            break;
        }
        default: {
            DEBUG("[TRACE] Unhandled event type: " << event.type << std::endl);
            break;
        }
    }
}

void Game::render() const {
    window->clear();

    window->draw(board);

    window->display();
}

int Game::run() {
    while (window->isOpen()) {
        for (auto event = sf::Event{}; window->pollEvent(event);) {
            on_event(event);
        }
        render();
    }

    return 0;
}
