#include <string>
#include <unordered_map>
#include <memory>

#include "ResourceManger/Resource.hpp"

class ResourceManager {
public:

    static ResourceManager* getPtr();
    static ResourceManager& getRef();

    void* getResource(const std::string& path);

    void unload();

private:
    static ResourceManager m_manager;
    std::unordered_map<std::string, std::unique_ptr<Resource>> resources;
};