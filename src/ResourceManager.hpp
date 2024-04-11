#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>

#ifdef THREADSAFE_MANAGER
#include <mutex>
#endif

class ResourceManager {
public:
    static void setPrefix(std::string prefix);
    static ResourceManager& get();

    const sf::Texture& texture(std::string path);

private:
    static ResourceManager *instance;
    static std::string prefix;
#ifdef THREADSAFE_MANAGER
    static std::mutex mutex;
#endif

    std::unordered_map<std::string, sf::Texture> textureMap;
};
