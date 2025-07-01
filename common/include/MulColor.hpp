#pragma once

#include <SFML/Graphics/Color.hpp>

struct MulColor : public sf::Color {
    MulColor();
    MulColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
    MulColor(const sf::Color& color);
    MulColor(const sf::Color& color, float mul);
    MulColor operator*(float f) const;
    MulColor& operator*=(float f);
    MulColor& operator=(const sf::Color& color);
};
