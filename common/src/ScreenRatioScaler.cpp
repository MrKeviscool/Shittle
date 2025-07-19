#include "ScreenRatioScaler.hpp"

void ScreenRatioScaler::ajustViewSize(sf::RenderWindow& window) const {
    const float currentRatio = ScreenRatioScaler::pixelsToRatio(window.getSize());
    if (currentRatio == desiredRatio) return;

    sf::FloatRect viewportSize;
    if (currentRatio > desiredRatio) {
        const float newWidth = desiredRatio / currentRatio;
        viewportSize = { (1.f - newWidth) / 2.f, 0.f, newWidth, 1.f };
    }
    else {
        const float newHeight = currentRatio / desiredRatio;
        viewportSize = { 0.f, (1.f - newHeight) / 2.f, 1.f, newHeight };
    }

    sf::View view = window.getView();
    view.setViewport(viewportSize);
    window.setView(view);
}

sf::Vector2f ScreenRatioScaler::getPixelOffset(const sf::RenderWindow& window) const {
    const float windowRatio = ScreenRatioScaler::pixelsToRatio(window.getSize());
    const sf::Vector2u windowSize = window.getSize();

    if (windowRatio == desiredRatio) return { 0.f, 0.f };
    if (windowRatio > desiredRatio) {
        const float viewWidth = static_cast<float>(windowSize.y) * desiredRatio;
        const float barSize = viewWidth - static_cast<float>(windowSize.x);
        return { barSize / 2.f, 0.f };
    }
    //todo, does not scale vertically yet.
    const float viewHeight = static_cast<float>(windowSize.x) / desiredRatio;
    const float barSize = viewHeight + static_cast<float>(windowSize.y);
    return { 0.f, barSize / 2.f };
}