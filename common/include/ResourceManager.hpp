#include <string>
#include <unordered_map>
#include <memory>

#include "ResourceManger/Resource.hpp"

class ResourceManager {
public:
    void* getResource(const std::string& path);

    void unloadAll();

private:
    std::unordered_map<std::string, std::unique_ptr<Resource>> resources;
};