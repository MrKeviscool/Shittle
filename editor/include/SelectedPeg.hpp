#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <Peg.hpp>

class SelectedPeg {
	SelectedPeg() = delete;
	SelectedPeg(Peg* peg);
private:
	Peg* peg;
	PegShape shapeType;
	char shapeData[sizeof(Bigger<sf::CircleShape, sf::RectangleShape>::type)];
	const float circSelectIncrease = 1.3f;
	const sf::Vector2f rectSelectIncrease{ 1.3f, 1.3f };
};