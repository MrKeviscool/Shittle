#include "ScreenRatioScaler.hpp"
#include <SFML/System/Vector2.hpp>

ScreenRatioScaler::ScreenRatioScaler(const sf::Vector2u baseScreenSize) : baseScreenSize(baseScreenSize) {
    baseRatio = getRatio(baseScreenSize.x, baseScreenSize.y);
}

void ScreenRatioScaler::ajustViewSize(sf::RenderWindow& window){
    const sf::Vector2u currentSize = window.getSize();
    const float currentRatio = getRatio(currentSize.x, currentSize.y);

    sf::FloatRect newViewportSize;
    if(currentRatio == baseRatio) return;

    if(currentRatio > baseRatio){
        const float newWidth = baseRatio / currentRatio;
        newViewportSize = { (1.f - newWidth) / 2.f, 0.f, newWidth, 1.f };
    }
    else {
        const float newHeight = currentRatio / baseRatio;
        newViewportSize = { 0.f, (1.f  - newHeight) / 2.f, 1.f, newHeight };
    }

    pixelOffset = {
        static_cast<int>(baseScreenSize.x - (baseScreenSize.x * newViewportSize.width)),
        static_cast<int>(baseScreenSize.y - (baseScreenSize.y * newViewportSize.height))
    };

    sf::View view = window.getView();
    view.setViewport(newViewportSize);
    window.setView(view);
}

sf::Vector2u baseScreenSize;
float baseRatio;
sf::Vector2i pixelOffset{ 0, 0};

constexpr float ScreenRatioScaler::getRatio(const float x, const float y) {
        return x/y;
}
