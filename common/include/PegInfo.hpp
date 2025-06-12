#pragma once

#include <SFML/System/Vector2.hpp>

#include "PegShape.hpp"

struct PegInfo {
    sf::Vector2f position;
    sf::Vector2f size;
    float rotation = 0;
    PegShape shape = PegShape::Circle;
};