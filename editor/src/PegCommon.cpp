#include "PegCommon.hpp"

#include <cmath>

#include "Algorithms.hpp"

void rotateInPlace(Peg* peg, const float rotationSteps) {
	rotateInPlace(peg->getShape(), peg->getSize(), rotationSteps);
}

void rotateInPlace(sf::Shape& peg, const sf::Vector2f size, const float rotation) {
	const sf::Vector2f pegSize = size;
	const sf::Vector2f halfPegSize{ pegSize.x / 2.f, pegSize.y / 2.f };
	
	const sf::Vector2f middle = getPointFromOffsets({0,0}, peg.getRotation(), halfPegSize);
	const sf::Vector2f rotatedMiddle = getPointFromOffsets({0,0}, peg.getRotation() + rotation, halfPegSize);
	const sf::Vector2f moveAmount = middle - rotatedMiddle;

	peg.move(moveAmount);
	peg.rotate(rotation);
}

void scaleInPlace(Peg* peg, const float scalePercent) {
	scaleInPlace(peg->getShape(), peg->getShapeType(), scalePercent);
}

void scaleInPlace(sf::Shape& peg, const PegShape shapeType, const float scalePercent) {
	if (shapeType == PegShape::Circle) {
		sf::CircleShape& circle = reinterpret_cast<sf::CircleShape&>(peg);
		const float originalSize = circle.getRadius() * 2.f;
		const float newSize = originalSize * scalePercent;
		
		const sf::Vector2f originalMiddlePos = getPointFromOffsets(circle.getPosition(), circle.getRotation(), {originalSize / 2.f, originalSize / 2.f});
		const sf::Vector2f scaledMiddlePos = getPointFromOffsets(circle.getPosition(), circle.getRotation(), {newSize / 2.f, newSize / 2.f});
		const sf::Vector2f moveAmount = originalMiddlePos - scaledMiddlePos;
		circle.setRadius(newSize / 2.f);
		circle.move(moveAmount);
	}
	else {
		sf::RectangleShape& rect = reinterpret_cast<sf::RectangleShape&>(peg);
		const sf::Vector2f originalSize = rect.getSize();
		const sf::Vector2f newSize {
			originalSize.x * scalePercent,
			originalSize.y * scalePercent,
		};

		const sf::Vector2f originalMiddlePos = getPointFromOffsets(rect.getPosition(), rect.getRotation(), rect.getSize() / 2.f);
		const sf::Vector2f scaledMiddlePos = getPointFromOffsets(rect.getPosition(), rect.getRotation(), newSize / 2.f);
		const sf::Vector2f moveAmount = originalMiddlePos - scaledMiddlePos;
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