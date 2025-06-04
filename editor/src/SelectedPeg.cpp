#include "SelectedPeg.hpp"

#include "PegCommon.hpp"

SelectedPeg::SelectedPeg(Peg* peg) : peg(peg), shapeData() {
	shapeType = peg->getShapeType();

	const sf::Vector2f selectShapeSize = getSelectedSize(peg);

	if (shapeType == PegShape::Circle) {
		new (shapeData) sf::CircleShape(selectShapeSize.x / 2.f);
	}
	else {
		new (shapeData) sf::RectangleShape(selectShapeSize);
	}

	sf::Shape* shape =
		reinterpret_cast<sf::Shape*>(shapeData);

	shape->setFillColor(sf::Color::Yellow);
	shape->setRotation(peg->getShape().getRotation());
	
	setSelectedPos(peg);
}

SelectedPeg::~SelectedPeg() {
	//reinterpret_cast<sf::Shape*>(shapeData)->~Shape();
}

SelectedPeg::operator Peg* () {
	return peg;
}

SelectedPeg::operator Peg* () const {
	return peg;
}

bool SelectedPeg::operator==(const SelectedPeg& other) const {
	return peg == other.peg;
}

bool SelectedPeg::operator==(const Peg* other) const {
	return peg == other;
}

Peg* SelectedPeg::getPeg() {
	return peg;
}

sf::Shape& SelectedPeg::getSelectShape() {
	return *reinterpret_cast<sf::Shape*>(shapeData);
}

Peg* SelectedPeg::getPeg() const {
	return peg;
}

const sf::Shape& SelectedPeg::getSelectShape() const {
	return *reinterpret_cast<const sf::Shape*>(shapeData);
}

sf::Vector2f SelectedPeg::getSelectSize() const {
	if (peg->getShapeType() == PegShape::Circle) {
		const sf::CircleShape* circle =
			reinterpret_cast<const sf::CircleShape*>(shapeData);
		const float rad = circle->getRadius();
		return { rad * 2.f, rad * 2.f };
	}
	else {
		const sf::RectangleShape* rect =
			reinterpret_cast<const sf::RectangleShape*>(shapeData);
		return rect->getSize();
	}
}

sf::Vector2f SelectedPeg::getSelectedSize(const Peg* target) const {
	if (target->getShapeType() == PegShape::Circle) {
		const float pegSize = target->getSize().x;
		const float selectSize = pegSize * circSelectIncrease;
		return { selectSize, 0 };
	}
	else {
		const sf::Vector2f pegSize = target->getSize();
		return { pegSize.x * rectSelectIncrease.x, pegSize.y * rectSelectIncrease.x };
	}
}

void SelectedPeg::setSelectedPos(const Peg* target){
	sf::Shape* shape = reinterpret_cast<sf::Shape*>(shapeData);

	const sf::Vector2f pegMiddle = getMiddlePosition(target);
	setMiddlePosition(*shape, peg->getShapeType(), pegMiddle);
}