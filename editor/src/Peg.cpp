#include "Peg.hpp"

#include <cmath>

Peg::Peg(const PegShape shape) : m_pegShape(shape){
    if (shape == PegShape::Circle) {
        new(m_shapeData) sf::CircleShape;
        reinterpret_cast<sf::CircleShape*>(m_shapeData)->setRadius(30.0f);
    }
    else {
        new(m_shapeData) sf::RectangleShape;
        reinterpret_cast<sf::RectangleShape*>(m_shapeData)->setSize({ 60.0f, 30.0f });
    }

    
}

PegShape Peg::getShapeType() const {
    return m_pegShape;
}

sf::Shape& Peg::getShape() {
    return *(reinterpret_cast<sf::Shape*>(m_shapeData));
}

const sf::Shape& Peg::getShape() const {
    return *(reinterpret_cast<const sf::Shape*>(m_shapeData));
} 

bool Peg::contains(const sf::Vector2f pos) const {
    if(m_pegShape == PegShape::Circle){
        const sf::CircleShape* shape = reinterpret_cast<const sf::CircleShape*>(m_shapeData);
        const sf::Vector2f middlePosition = {shape->getPosition().x + shape->getRadius(), shape->getPosition().y + shape->getRadius()};
        
        const float xDistance = pos.x - middlePosition.x;
        const float yDistance = pos.y - middlePosition.y;

        return std::abs(std::sqrt((xDistance*xDistance) + (yDistance*yDistance))) < shape->getRadius();
    }
    else{
        const sf::RectangleShape* shape = reinterpret_cast<const sf::RectangleShape*>(m_shapeData);

        return (shape->getPosition().x < pos.x && shape->getPosition().x + shape->getSize().x > pos.x
            && shape->getPosition().y < pos.y && shape->getPosition().y + shape->getSize().y > pos.y);
    }
}