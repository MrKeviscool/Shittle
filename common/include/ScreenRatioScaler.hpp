#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <type_traits>

#include <SFML/Graphics/RenderWindow.hpp>

class ScreenRatioScaler {
public:
    ScreenRatioScaler() = delete;
    ScreenRatioScaler(const sf::Vector2u baseScreenSize);
    void ajustViewSize(sf::RenderWindow& window);

private:
    sf::Vector2u baseScreenSize;
    float baseRatio;
    sf::Vector2i pixelOffset{ 0, 0};

    constexpr static float getRatio(const float x, const float y);
};
