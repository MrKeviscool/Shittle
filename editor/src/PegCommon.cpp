#include "PegCommon.hpp"

#include <cmath>

#include "Algorithms.hpp"

sf::Vector2f getPointFromOffsets(const sf::Vector2f origin, const float angle, const sf::Vector2f length){
	const float middleOffsetAngle = getAngle({ 0.f,0.f }, length);
	const float middleDistance = getDistance({ 0.f,0.f }, length);
	return getPoint(angle + middleOffsetAngle, middleDistance);
}

void rotateInPlace(Peg* peg, const int rotationSteps) {
	rotateInPlace(peg->getShape(), peg->getSize(), rotationSteps);
}

void rotateInPlace(sf::Shape& peg, const sf::Vector2f size, const int rotationSteps) {
	const float rotation = rotationSteps * 5.f;
	const sf::Vector2f pegSize = size;
	const sf::Vector2f halfPegSize{ pegSize.x / 2.f, pegSize.y / 2.f };

	const float curAngle = peg.getRotation();
	const float middleDistance = getDistance({ 0.f,0.f }, halfPegSize);
	const float middleOffsetAngle = getAngle({ 0.f,0.f }, halfPegSize);

	const sf::Vector2f middle = getPoint(curAngle + middleOffsetAngle, middleDistance);
	const sf::Vector2f moveAmount = middle - getPoint(curAngle + middleOffsetAngle + rotation, middleDistance);

	peg.move(moveAmount);
	peg.rotate(rotation);
}

void resizeInPlace(Peg* peg, const int resizeSteps) {
	resizeInPlace(peg->getShape(), peg->getShapeType(), resizeSteps);
}

void resizeInPlace(sf::Shape& peg, const PegShape shapeType, const int resizeSteps) {
	if (shapeType == PegShape::Circle) {
		sf::CircleShape& circle = reinterpret_cast<sf::CircleShape&>(peg);
		const float originalSize = circle.getRadius();

		const float newSize =
			originalSize * std::pow(1.1f, static_cast<float>(resizeSteps));

		const float moveAmount = (originalSize - newSize);

		circle.setRadius(newSize);
		circle.move(moveAmount, moveAmount);
	}
	else {
		sf::RectangleShape& rect = reinterpret_cast<sf::RectangleShape&>(peg);
		const sf::Vector2f originalSize = rect.getSize();
		const sf::Vector2f newSize = {
			originalSize.x * std::pow(1.1f, static_cast<float>(resizeSteps)),
			originalSize.y * std::pow(1.1f, static_cast<float>(resizeSteps)),
		};

		const sf::Vector2f moveAmount = { (originalSize.x - newSize.x) / 2.f, (originalSize.y - newSize.y) / 2.f};
		rect.setSize(newSize);
		rect.move(moveAmount);
	}
}

Peg* getPegAtPosition(const sf::Vector2f pos, std::forward_list<Peg>& pegs) {
	for (auto& peg : pegs)
		if (peg.contains(pos)) return &peg;
	return nullptr;
}

Peg* getPegAtPosition(const sf::Vector2i pos, std::forward_list<Peg>& pegs) {
	const sf::Vector2f floatPos{ static_cast<float>(pos.x), static_cast<float>(pos.y) };
	for (auto& peg : pegs)
		if (peg.contains(floatPos)) return &peg;
	return nullptr;
}

Peg* getPegOnMouse(const InputState& input, std::forward_list<Peg>& pegs) {
	for (auto& peg : pegs) {
		if (peg.contains({ static_cast<float>(input.mousePos().x), static_cast<float>(input.mousePos().y) }))
			return &peg;
	}
	return nullptr;
}

std::vector<Peg*> getPegsOnMouse(const InputState& input, std::forward_list<Peg>& pegs) {
	std::vector<Peg*> out;
	for (auto& peg : pegs) {
		if (peg.contains({ static_cast<float>(input.mousePos().x), static_cast<float>(input.mousePos().y) }))
			out.push_back(&peg);
	}
	return out;
}