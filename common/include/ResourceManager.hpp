#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <fstream>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Font.hpp>

#include "ResourceManagerResource.hpp"

using BinaryBlobVec = std::vector<uint8_t>;

class ResourceManager {
public:
    
    template<typename T>
    T* getResource(const std::string& path);
    template<>
    sf::Image* getResource<sf::Image>(const std::string& path);
    template<>
    sf::Font* getResource<sf::Font>(const std::string& path);

    template<typename T>
    void createVirtualResource(std::unique_ptr<T> resource, const std::string& path);

    void unloadAll();
    void unload(const std::string& path);

private:
    std::unordered_map<std::string, ResourceManagerResource> resources;
    std::unique_ptr<BinaryBlobVec> loadResourceBin(const std::string& path);
};

template<typename T>
inline T* ResourceManager::getResource(const std::string& path) {
    const auto resourcePositionIter = resources.find(path);
    if (resourcePositionIter == resources.end()) {
        std::unique_ptr<BinaryBlobVec> fileData = loadResourceBin(path);
        if (!fileData) return nullptr;
		resources.emplace(path, fileData.release());
       return static_cast<T*>(resources.at(path).resource);
    }
    return static_cast<T*>(resourcePositionIter->second.resource);
}

template<>
inline sf::Image* ResourceManager::getResource<sf::Image>(const std::string& path) {
    const auto resourcePositionIter = resources.find(path);
    if (resourcePositionIter == resources.end()) {
        auto image = std::make_unique<sf::Image>();
        const auto imageLoadSuccess = image->loadFromFile(path);
        if (!imageLoadSuccess) return nullptr;
        resources.emplace(path, image.release());
        return static_cast<sf::Image*>(resources.at(path).resource);
    }
    return static_cast<sf::Image*>(resourcePositionIter->second.resource);
}

template<>
inline sf::Font* ResourceManager::getResource<sf::Font>(const std::string& path) {
    const auto resourcePositionIter = resources.find(path);
    if (resourcePositionIter == resources.end()) {
        auto font = std::make_unique<sf::Font>();
        const auto imageLoadSuccess = font->loadFromFile(path);
        if (!imageLoadSuccess) return nullptr;
        resources.emplace(path, font.release());
        return static_cast<sf::Font*>(resources.at(path).resource);
    }
    return static_cast<sf::Font*>(resourcePositionIter->second.resource);
}

template<typename T>
inline void ResourceManager::createVirtualResource(std::unique_ptr<T> resource, const std::string& path) {
    resources.emplace(path, resource.release());
}
