#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "ResourceManager.hpp"

int main() {
    ResourceManager::setPrefix("assets/");
    Game g;

    return g.run();
}
