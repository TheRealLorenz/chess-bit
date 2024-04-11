#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>

class ResourceManager {
public:
    static void setPrefix(std::string prefix);
    static ResourceManager& get();

    const sf::Texture& texture(std::string path);

private:
    static ResourceManager *instance;
    static std::string prefix;

    std::unordered_map<std::string, sf::Texture> textureMap;
};
