#include "ResourceManger/Resource.hpp"

Resource::Resource(const std::string& path) : path(path)
{

}

const std::string& Resource::getPath() const {
    return path;
}

