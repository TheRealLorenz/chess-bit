#pragma once

#include <string>
#include <unordered_map>

#include "SFML/Graphics/Texture.hpp"

#ifdef THREADSAFE_MANAGER
#include <mutex>
#endif

class ResourceManager {
public:
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(const ResourceManager&) = delete;

    static void setPrefix(std::string prefix);
    static ResourceManager& get();

    const sf::Texture& texture(std::string path);

private:
    ResourceManager() {}
    static ResourceManager *instance;
    static std::string prefix;
#ifdef THREADSAFE_MANAGER
    static std::mutex mutex;
#endif

    std::unordered_map<std::string, sf::Texture> textureMap;
};
