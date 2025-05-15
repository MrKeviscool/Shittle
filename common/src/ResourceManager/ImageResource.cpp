#include "ResourceManger/ImageResource.hpp"


#include <stdexcept>

ImageResource::ImageResource(const std::string& path) : Resource(path) 
{
    if(!image.loadFromFile(path))
        throw std::runtime_error(std::string("error loading file: ") + path);
    
}

void* ImageResource::getResource() {
    return static_cast<void*>(&image);
}