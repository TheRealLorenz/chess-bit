#include "ResourceManager.hpp"
#include "SFML/Graphics/Texture.hpp"

ResourceManager *ResourceManager::instance = nullptr;
std::string ResourceManager::prefix = "";

ResourceManager& ResourceManager::get() {
    if (!instance) {
        instance = new ResourceManager();
    }

    return *instance;
}

void ResourceManager::setPrefix(std::string prefix) {
    ResourceManager::prefix = prefix;
}

const sf::Texture& ResourceManager::texture(std::string path) {
    if (textureMap.find(path) == textureMap.end()) {
        textureMap[path].loadFromFile(prefix + path);
    }

    return textureMap[path];
}
