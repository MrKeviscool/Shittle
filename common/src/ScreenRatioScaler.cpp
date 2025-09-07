#include "ScreenRatioScaler.hpp"
#include <SFML/System/Vector2.hpp>

ScreenRatioScaler::ScreenRatioScaler(const sf::Vector2u baseWindowSize) : baseWindowSize(baseWindowSize), curWindowSize(baseWindowSize) {
    baseRatio = getRatio(baseWindowSize.x, baseWindowSize.y);
}

void ScreenRatioScaler::adjustViewSize(sf::RenderWindow& window){
    curWindowSize = window.getSize();
    const float currentRatio = getRatio(curWindowSize.x, curWindowSize.y);

    if(currentRatio == baseRatio) return;

    if(currentRatio > baseRatio){
        const float newWidth = baseRatio / currentRatio;
        viewportSize = { newWidth, 1.f};
    }
    else {
        const float newHeight = currentRatio / baseRatio;
        viewportSize = { 1.f, newHeight};
    }

    sf::View view = window.getView();
    view.setViewport({(1.f - viewportSize.x) / 2.f, (1.f - viewportSize.y) / 2.f, viewportSize.x, viewportSize.y});
    window.setView(view);
}

sf::Vector2f ScreenRatioScaler::getPixelScale() const {
    const sf::Vector2f viewSize{curWindowSize.x * viewportSize.x, curWindowSize.y * viewportSize.y};
    return {
        static_cast<float>(baseWindowSize.x) / viewSize.x,
        static_cast<float>(baseWindowSize.y) / viewSize.y,
    };
}

sf::Vector2f ScreenRatioScaler::getPixelBaseOffset() const {
    const sf::Vector2f viewSize{curWindowSize.x * viewportSize.x, curWindowSize.y * viewportSize.y};
    const sf::Vector2f difference{curWindowSize.x - viewSize.x, curWindowSize.y - viewSize.y};
    return {difference.x / 2.f, difference.y / 2.f};
}

constexpr float ScreenRatioScaler::getRatio(const float x, const float y) {
    return x/y;
}

constexpr float ScreenRatioScaler::getRatio(const unsigned int x, const unsigned int y) {
    return static_cast<float>(x) / static_cast<float>(y);
}
