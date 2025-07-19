#pragma once

#include <type_traits>

#include <SFML/Graphics/RenderWindow.hpp>

class ScreenRatioScaler {
public:
    
    ScreenRatioScaler() = delete;

    ScreenRatioScaler(const float desiredRatio) : desiredRatio(desiredRatio) {
    }

    template<typename T>
    ScreenRatioScaler(const T screenSize) : desiredRatio(ScreenRatioScaler::pixelsToRatio(screenSize)) {
    }

    void ajustViewSize(sf::RenderWindow& window) const;
    sf::Vector2f getPixelOffset(const sf::RenderWindow& window) const;

private:
    float desiredRatio;
    template<typename T>
    static inline float pixelsToRatio(const T pixels) {
        return static_cast<float>(pixels.x) / static_cast<float>(pixels.y);
    }
    template<typename T>
    static inline float pixelsToRatio(const T x, const T y) {
        return static_cast<float>(x) / static_cast<float>(y);
    }
};

