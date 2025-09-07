#pragma once

#include <vector>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Image.hpp>

#include "PegShape.hpp"

struct SerializedPeg {
    sf::Vector2f position;
    sf::Vector2f size;
    float rotation;
    PegShape shape;
};

struct SerializedLevel {
    std::vector<SerializedPeg> pegs;
    std::vector<sf::Image> backgrounds;
    std::vector<sf::Image> thumbnails;
};