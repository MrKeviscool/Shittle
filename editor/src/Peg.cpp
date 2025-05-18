#include "Peg.hpp"

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