#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "PegShape.hpp"
#include "SerializedData.hpp"

class Peg{
public:
    Peg(const PegShape pegShape);
    Peg(const Peg& other);
	~Peg();

	Peg& operator=(const Peg& other);
	Peg& operator=(Peg&& other);
	Peg& operator=(PegShape pegShape);

    PegShape getShapeType() const;
    sf::Shape& getShape();
    const sf::Shape& getShape() const;
    bool contains(const sf::Vector2f pos) const;
    
    sf::Vector2f getSize() const;
    void setSize(const sf::Vector2f size);

    operator SerializedPeg() const;

private:
    PegShape shapeType;
	union {
		sf::CircleShape circleShape;
		sf::RectangleShape rectangleShape;
	};
	void destructShape();
};
