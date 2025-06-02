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

void drawSelected(sf::RenderWindow& window, const std::unordered_set<SelectedPeg>& selectedPegs) {
	for (const SelectedPeg& selectedPeg : selectedPegs) {
		window.draw(selectedPeg.getSelectShape());
	}
}