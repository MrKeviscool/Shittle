#include "SelectedPeg.hpp"

SelectedPeg::SelectedPeg(Peg* peg) : peg(peg), shapeData() {
	shapeType = peg->getShapeType();
	sf::Shape* shape = nullptr;

	if (shapeType == PegShape::Circle) {
		sf::CircleShape* circle =
			reinterpret_cast<sf::CircleShape*>(
				new (shapeData) sf::CircleShape(peg->getSize().x * circSelectIncrease)
			);
		shape = circle;
		circle->setPosition(peg->getShape().getPosition() - sf::Vector2f(circle->getRadius() / 2.0f, circle->getRadius() / 2.0f));
	}
	else {

	}
}