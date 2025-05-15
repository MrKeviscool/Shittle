#pragma once

#include <SFML/Graphics/Image.hpp>

#include "Resource.hpp"

class ImageResource : public Resource {
public:
    ImageResource(const std::string& path);

    void* getResource() override;

protected:
    sf::Image image;
};