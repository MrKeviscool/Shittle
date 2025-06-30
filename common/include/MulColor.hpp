#pragma once

#include <SFML/Graphics/Color.hpp>

struct MulColor : public sf::Color {
    MulColor();
    MulColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
    MulColor operator*(float f) const;
    MulColor& operator*=(float f);

};
