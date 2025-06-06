#pragma once

#include <SFML/System/Vector2.hpp>

#include "PegShape.hpp"

struct PegInfo {
    sf::Vector2f position;
    sf::Vector2f size;
    float rotation;
    PegShape shape;
private:
    char _padding[3];
};