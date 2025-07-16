#include "DrawCommon.hpp"
#include "SelectedPeg.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

void drawButtons(sf::RenderWindow& window, const Scaler& scaler, const std::unordered_map<ButtonType, Button>& buttons) {
    for (auto& butt : buttons){
        sf::RectangleShape scaledShape = butt.second.getShape();
        scaler.apply(scaledShape);
        butt.second.draw(window);
    }
}

void drawCursorType(sf::RenderWindow& window, const Scaler& scaler, bool isButtonHovered, sf::Vector2i mousePos, CursorType& cursorType) {
    if (!cursorType.isCursor && !isButtonHovered) {
        cursorType.peg.getShape().setPosition({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) });
        scaler.apply(cursorType.peg.getShape());
	window.draw(cursorType.peg.getShape());
	window.setMouseCursorVisible(false);
    }
    else window.setMouseCursorVisible(true);
}

void drawPegs(sf::RenderWindow& window, const Scaler& scaler, std::forward_list<Peg>& pegs) {
    for (auto& peg : pegs){
        scaler.apply(peg.getShape());
        window.draw(peg.getShape());
    }
}

void drawSelected(sf::RenderWindow& window, const Scaler& scaler, std::unordered_set<SelectedPeg>& selectedPegs) {
    for (const SelectedPeg& selectedPeg : selectedPegs) {
        scaler.apply(const_cast<SelectedPeg&>(selectedPeg).getSelectShape()); //is actually safe but need cast because std::set prevents modifying (as it can cause a need to rehash)
        window.draw(selectedPeg.getSelectShape());
    }
}
