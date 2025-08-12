#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <type_traits>

#include <SFML/Graphics/RenderWindow.hpp>

class ScreenRatioScaler {
public:
    ScreenRatioScaler() = delete;
    ScreenRatioScaler(const sf::Vector2u baseWindowSize);
    void ajustViewSize(sf::RenderWindow& window);
    sf::Vector2f getPixelScale() const;
    sf::Vector2f getPixelBaseOffset() const;
    
private:
    sf::Vector2u baseWindowSize;
    sf::Vector2u curWindowSize;
    sf::Vector2f viewportSize{1.f, 1.f};
    float baseRatio;

    constexpr static float getRatio(const float x, const float y);
    constexpr static float getRatio(const unsigned int x, const unsigned int y);
};
