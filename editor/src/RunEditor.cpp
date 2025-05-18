#include "RunEditor.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

#include "Button.hpp"
#include "InputState.hpp"
#include "ResourceManager.hpp"
#include "Peg.hpp"

bool askToExit(sf::RenderWindow& window, InputState& input, ResourceManager& resources) {
	const sf::Font* textFont = static_cast<sf::Font*>(resources.getResource("resources/robotto.ttf"));

	Button yesButton({ 200, 100 }, { 1920 / 4, 1080 * 0.75f }, static_cast<sf::Texture*>(resources.getResource("resources/okButton.png")));
	Button noButton({ 200, 100 }, { 1920 * 0.75f, 1080 * 0.75f }, static_cast<sf::Texture*>(resources.getResource("resources/cancelButton.png")));

	sf::Text exitText("exit editor?", *textFont, 60);
	exitText.setPosition((1920 / 2 - exitText.getGlobalBounds().width / 2), 1080 / 4);


	yesButton.setText("exit", textFont, 20.0f);
	noButton.setText("cancel", textFont, 20.0f);

	window.setMouseCursorVisible(true);
	while (window.isOpen()) {
		input.pollEvents();
		if (yesButton.poll()) return true;
		if (noButton.poll()) return false;
		window.clear();
		yesButton.draw(window);
		noButton.draw(window);
		window.draw(exitText);
		window.display();
	}
	return false;
}

struct CursorType {
	Peg peg;
	bool isCursor = true;
	CursorType() : peg(PegShape::Circle) {};
	CursorType(const Peg peg, const bool isCursor) : peg(peg), isCursor(isCursor) {};
	CursorType& operator=(CursorType&& other) = default;
};

void runEditor(sf::RenderWindow& window, InputState& input, ResourceManager& resources, std::vector<Button>& buttons) {

	CursorType cursorType;

	buttons[0].setFunction([&cursorType]() {cursorType = CursorType(Peg(PegShape::Circle), false); });
	buttons[1].setFunction([&cursorType]() {cursorType = CursorType(Peg(PegShape::Rect), false); });
	buttons[2].setFunction([&cursorType]() {cursorType = CursorType(cursorType.peg, true); });


	while (window.isOpen()) {
		input.pollEvents();

		for (auto& keyEvnt : input.keyEvents) {
			if (keyEvnt.event.code == sf::Keyboard::Escape &&
				keyEvnt.buttonState == InputState::ButtonState::released) 
			{
				if (askToExit(window, input, resources)) window.close();
			}
		}

		window.clear();

		bool buttonIsHovered = false;
		for (auto& butt : buttons) {
			if (butt.isHovering()) buttonIsHovered = true;
			butt.poll();
			butt.draw(window);
		}

		if (!buttonIsHovered && !cursorType.isCursor) {
			cursorType.peg.getShape().setPosition({static_cast<float>(input.mousePos.x), static_cast<float>(input.mousePos.y) });
			window.draw(cursorType.peg.getShape());
			window.setMouseCursorVisible(false);
		}
		else {
			window.setMouseCursorVisible(true);
		}

		window.display();

	}
}