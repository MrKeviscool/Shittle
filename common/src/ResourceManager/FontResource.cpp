#include "ResourceManger/FontResource.hpp"

FontResource::FontResource(const std::string& path) : Resource(path){
    if(!font.loadFromFile(path))
        throw std::exception();
}

void* FontResource::getResource() {
    return &font;
}