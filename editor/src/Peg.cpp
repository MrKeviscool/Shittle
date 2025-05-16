#include "Peg.hpp"

Peg::Peg(const PegShape shape, const PegType type) : m_pegShape(shape), m_pegType(type) {
    if(shape == PegShape::Circle)
        new(m_shapeData) sf::CircleShape;
    else new(m_shapeData) sf::RectangleShape;
}

PegShape Peg::getShape() const {
    return m_pegShape;
}

PegType Peg::getType() const {
    return m_pegType;
}