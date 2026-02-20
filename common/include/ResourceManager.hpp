#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "ResourceManagerResource.hpp"

class ResourceManager {
public:
    void* getResource(const std::string& path);

    void createVirtualResource(void* resource, const std::string& path);

    void unloadAll();
    void unload(const std::string& path);

private:
    void* createResource(const std::string& path);
    std::unordered_map<std::string, Resource> resources;
};