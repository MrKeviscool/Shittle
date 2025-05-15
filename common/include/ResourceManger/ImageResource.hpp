#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "Resource.hpp"

class ImageResource : public Resource {
public:
    ImageResource(const std::string& path);

    void* getResource() override;

protected:
    sf::Texture image;
};