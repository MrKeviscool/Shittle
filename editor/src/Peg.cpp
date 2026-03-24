#include "Peg.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Algorithms.hpp"
#include "PegShape.hpp"

const float defualtCircleRad = 30.f;
const sf::Vector2f defaultRectSize = {60.f, 30.f};

Peg::Peg(const PegShape shape) : shapeType(shape){
	if(shape == PegShape::Circle)
		new(&circleShape) sf::CircleShape(defualtCircleRad);
	else 
		new(&rectangleShape) sf::RectangleShape(defaultRectSize);
}

Peg::Peg(const Peg& other) : shapeType(other.shapeType) {
	if(shapeType == PegShape::Circle)
		new(&circleShape) sf::CircleShape(other.circleShape);
	else new(&rectangleShape) sf::RectangleShape(other.rectangleShape);
}

Peg::~Peg(){
	destructShape();
}

Peg& Peg::operator=(const Peg& other){
	destructShape();

	shapeType = other.shapeType;
	if(shapeType == PegShape::Circle)
		new(&circleShape) sf::CircleShape(other.circleShape);
	else new(&rectangleShape) sf::RectangleShape(other.rectangleShape);
	return *this;
}

Peg& Peg::operator=(Peg&& other){
	destructShape();

	shapeType = other.shapeType;
	if(shapeType == PegShape::Circle)
		new (&circleShape) sf::CircleShape(std::move(other.circleShape));
	else new(&rectangleShape) sf::RectangleShape(std::move(other.rectangleShape));
	return *this;
}

Peg& Peg::operator=(PegShape pegShape){
	destructShape();

	shapeType = pegShape;
	if(pegShape == PegShape::Circle)
		new (&circleShape) sf::CircleShape(defualtCircleRad);
	else new (&rectangleShape) sf::RectangleShape(defaultRectSize);
	return *this;
}

PegShape Peg::getShapeType() const {
    return shapeType;
}

sf::Shape& Peg::getShape() {
    return *(reinterpret_cast<sf::Shape*>(&circleShape));
}

const sf::Shape& Peg::getShape() const {
    return *(reinterpret_cast<const sf::Shape*>(&circleShape));
} 

bool Peg::contains(const sf::Vector2f pos) const {
    if(shapeType == PegShape::Circle){
        const sf::Vector2f middlePosition = {circleShape.getPosition().x + circleShape.getRadius(), circleShape.getPosition().y + circleShape.getRadius()};
        const sf::Vector2f distanceFromMiddle = pos - middlePosition;

        return getDistance({0,0}, distanceFromMiddle) < circleShape.getRadius();
    }
    else
        return rectangleShape.getGlobalBounds().contains(pos);
}

sf::Vector2f Peg::getSize() const {
    if (shapeType == PegShape::Circle) {
        const float diamiter = circleShape.getRadius() * 2.f;
        return { diamiter, diamiter };
    }
    else 
        return rectangleShape.getSize();
}

void Peg::setSize(const sf::Vector2f newSize) {
    if(shapeType == PegShape::Circle)
        circleShape.setRadius(newSize.x / 2);
    else
        setSize(newSize);
}

Peg::operator SerializedPeg() const {
    const auto& shape = getShape();
    SerializedPeg info;
    info.position = shape.getPosition();
    info.size = getSize();
    info.rotation = shape.getRotation();
    info.shape = shapeType;
    return info;
}

void Peg::destructShape(){
	if(shapeType == PegShape::Circle)
		circleShape.~CircleShape();
	else rectangleShape.~RectangleShape();
}
