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
	setSelectedPos(peg, selectShapeSize);
	

	reinterpret_cast<sf::Shape*>(shapeData)->setFillColor(sf::Color::Yellow);
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
		return { rad, rad };
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

void SelectedPeg::setSelectedPos(const Peg* target, const sf::Vector2f selectSize){
	const sf::Vector2f pegPos = target->getShape().getPosition();
	if (shapeType == PegShape::Circle) {
		const float pegSize = target->getSize().x;
		const float sizeDifference = selectSize.x - pegSize;

		const sf::Vector2f setPos{
			pegPos.x - (sizeDifference / 2.f),
			pegPos.y - (sizeDifference / 2.f),
		};

		sf::CircleShape* circle =
			reinterpret_cast<sf::CircleShape*>(shapeData);
		circle->setPosition(setPos);
	}
	else {
		const sf::Vector2f pegSize = target->getSize();
		const sf::Vector2f selectSize{
			pegSize.x * rectSelectIncrease.x,
			pegSize.y * rectSelectIncrease.y
		};
		const sf::Vector2f sizeDifference = selectSize - pegSize;
		const sf::Vector2f setPos{
			pegPos.x - (sizeDifference.x / 2.f),
			pegPos.y - (sizeDifference.y / 2.f),
		};

		sf::RectangleShape* rect =
			reinterpret_cast<sf::RectangleShape*>(shapeData);
		rect->setPosition(setPos);
	}
}