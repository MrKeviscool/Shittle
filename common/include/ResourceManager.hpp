#include <string>
#include <unordered_map>
#include <memory>

#include "ResourceManger/Resource.hpp"

class ResourceManager {
public:

    static ResourceManager* getPtr();
    static ResourceManager& getRef();

    Resource* getResource(std::string& path);

private:
    static ResourceManager m_manager;
    std::unordered_map<std::string, std::unique_ptr<Resource>> resources;
};