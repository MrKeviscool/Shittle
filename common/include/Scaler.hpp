#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

class Scaler {
public:
    Scaler() = delete;
    Scaler(sf::Vector2u baseWindowSize, sf::Vector2u currentWindowSize);

    void setNewWindowSize(sf::Vector2u);
    void apply(sf::Transformable& transformable) const;

private:
    sf::Vector2f scaleFactor;
    sf::Vector2u baseWindowSize;
};
