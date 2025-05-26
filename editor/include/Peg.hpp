#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "Bigger.hpp"

class Peg{
public:
    Peg(const PegShape pegShape);
    PegShape getShapeType() const;
    sf::Shape& getShape();
    const sf::Shape& getShape() const;
    bool contains(const sf::Vector2f pos) const;
    
    sf::Vector2f getSize() const;

private:
    PegShape m_pegShape;
    alignas(Bigger<sf::CircleShape, sf::RectangleShape>::type) 
        char m_shapeData[sizeof(Bigger<sf::CircleShape, sf::RectangleShape>::type)];
};