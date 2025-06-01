#include "DrawCommon.hpp"

void drawButtons(sf::RenderWindow& target, const std::unordered_map<ButtonType, Button>& buttons) {
	for (auto& butt : buttons)
		butt.second.draw(target);
}

void drawCursorType(sf::RenderWindow& window, bool isButtonHovered, sf::Vector2i mousePos, CursorType& cursorType) {
	if (!cursorType.isCursor && !isButtonHovered) {
		cursorType.peg.getShape().setPosition({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) });
		window.draw(cursorType.peg.getShape());
		window.setMouseCursorVisible(false);
	}
	else
		window.setMouseCursorVisible(true);
}

void drawPegs(sf::RenderWindow& window, const std::forward_list<Peg>& pegs) {
	for (auto& peg : pegs)
		window.draw(peg.getShape());
}

void drawSelected(sf::RenderWindow& window, const std::unordered_set<Peg*>& selectedPegs) {
	for (Peg* peg : selectedPegs) {

		if (peg->getShapeType() == PegShape::Circle) {
			const sf::CircleShape* shape = static_cast<sf::CircleShape*>(&peg->getShape());
			const float radius = shape->getRadius() * 1.5f;

			sf::CircleShape shapeToDraw(radius);
			shapeToDraw.setPosition(peg->getShape().getPosition() - sf::Vector2f(shape->getRadius() / 2.0f, shape->getRadius() / 2.0f));
			shapeToDraw.setFillColor(sf::Color::Yellow);
			window.draw(shapeToDraw);
		}

		else {
			const sf::RectangleShape* shape = static_cast<sf::RectangleShape*>(&peg->getShape());
			sf::RectangleShape shapeToDraw(shape->getSize() * 1.5f);
			shapeToDraw.setFillColor(sf::Color::Yellow);
			shapeToDraw.setPosition(shape->getPosition() - (shape->getSize() / 4.0f));
			shapeToDraw.setRotation(peg->getShape().getRotation());
			window.draw(shapeToDraw);
		}
	}
}