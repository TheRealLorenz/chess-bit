#include "ResourceManager.hpp"

#include "SFML/Graphics/Texture.hpp"

ResourceManager *ResourceManager::instance = nullptr;
std::string ResourceManager::prefix = "";

ResourceManager& ResourceManager::get() {
#ifdef THREADSAFE_MANAGER
    std::lock_guard<std::mutex> lock(mutex);
#endif

    if (!instance) {
        instance = new ResourceManager();
    }

    return *instance;
}

void ResourceManager::setPrefix(std::string prefix) {
    ResourceManager::prefix = prefix;
}

const sf::Texture& ResourceManager::texture(std::string path) {
#ifdef THREADSAFE_MANAGER
    std::lock_guard<std::mutex> lock(mutex);
#endif

    if (textureMap.find(path) == textureMap.end()) {
        textureMap[path].loadFromFile(prefix + path);
    }

    return textureMap[path];
}
