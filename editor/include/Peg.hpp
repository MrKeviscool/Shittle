#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "Bigger.hpp"
#include "PegShape.hpp"
#include "SerializedData.hpp"

class Peg{
public:
    Peg(const PegShape pegShape);
    Peg(const Peg& other);

    PegShape getShapeType() const;
    sf::Shape& getShape();
    const sf::Shape& getShape() const;
    bool contains(const sf::Vector2f pos) const;
    
    sf::Vector2f getSize() const;
    void setSize(const sf::Vector2f size);

    operator SerializedPeg() const;

private:
    PegShape m_pegShape;
    uint8_t m_shapeData[sizeof(Bigger<sf::CircleShape, sf::RectangleShape>::type)];
};