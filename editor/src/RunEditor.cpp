#include "RunEditor.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <chrono>

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
		for (auto& event : input.keyEvents) {
			if (event.event.code == sf::Keyboard::Escape
				&& event.buttonState == InputState::ButtonState::released
				) return false;
		}
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

void placePeg(const InputState& input, const CursorType& cursorType, std::vector<Peg>& pegs) {
	pegs.emplace_back(cursorType.peg);
}

bool clickedMouse(InputState& input){
	const std::chrono::milliseconds maxClickLength(200);

	for(auto iter = input.mouseEvents.begin(); iter != input.mouseEvents.end(); iter++){
		if(iter == input.mouseEvents.end() - 1 && iter->buttonState != InputState::ButtonState::released)
		return false;
	}

	auto startTime = std::chrono::steady_clock::now();
	while(std::chrono::steady_clock::now() - startTime > maxClickLength){
		input.pollEvents();
		for(auto& evnt : input.mouseEvents){
			if(evnt.event.button == sf::Mouse::Button::Left && evnt.buttonState == InputState::ButtonState::released)
				return false;
		}
	}
	return true;
};

void selectPeg(const InputState& input, std::vector<Peg>& pegs, std::vector<Peg*>& selectedPegs){
	for(auto& peg : pegs){
		if(peg.contains({static_cast<float>(input.mousePos.x), static_cast<float>(input.mousePos.y)}))
			selectedPegs.push_back(&peg);
	}
}

void moveSelected(const InputState& input, const sf::Vector2f mouseOrigin, const std::vector<Peg*>& selected){

}

void drawSelected(sf::RenderTarget& window, const std::vector<Peg*>& selectedPegs){
	for(Peg* peg : selectedPegs){
		if(peg->getShapeType() == PegShape::Circle){
			const sf::CircleShape* shape = static_cast<sf::CircleShape*>(&peg->getShape());
			const float radius = shape->getRadius() * 1.5f;

			sf::CircleShape shapeToDraw(radius);
			shapeToDraw.setPosition(peg->getShape().getPosition() - sf::Vector2f(shape->getRadius()/2.0f, shape->getRadius()/2.0f));
			shapeToDraw.setFillColor(sf::Color::Yellow);
			window.draw(shapeToDraw);
		}
		
		else{
			const sf::RectangleShape* shape = static_cast<sf::RectangleShape*>(&peg->getShape());
			sf::RectangleShape shapeToDraw(shape->getSize() * 1.5f);

			shapeToDraw.setPosition(shape->getPosition() - (shape->getSize()/4.0f));
			shapeToDraw.setFillColor(sf::Color::Yellow);
			window.draw(shapeToDraw);
		}
	}
}

void runEditor(sf::RenderWindow& window, InputState& input, ResourceManager& resources, std::unordered_map<std::string, Button>& buttons) {

	CursorType cursorType;

	buttons["cursorPeg"].setFunction([&cursorType]() {cursorType = CursorType(Peg(PegShape::Circle), false); });
	buttons["cursorBrick"].setFunction([&cursorType]() {cursorType = CursorType(Peg(PegShape::Rect), false); });
	buttons["cursorSelect"].setFunction([&cursorType]() {cursorType = CursorType(cursorType.peg, true); });

	std::vector<Peg> pegs;
	std::vector<Peg*> selectedPegs;

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
			if (butt.second.isHovering()) buttonIsHovered = true;
			butt.second.poll();
			butt.second.draw(window);
		}

		for (auto& mouseEvnt : input.mouseEvents) {
			if (!buttonIsHovered && mouseEvnt.event.button == sf::Mouse::Left && mouseEvnt.buttonState == InputState::ButtonState::released) {
				if (!cursorType.isCursor) placePeg(input, cursorType, pegs);
				else selectPeg(input, pegs, selectedPegs);
			}
		}

		if (!buttonIsHovered && !cursorType.isCursor) {
			cursorType.peg.getShape().setPosition({static_cast<float>(input.mousePos.x), static_cast<float>(input.mousePos.y) });
			window.draw(cursorType.peg.getShape());
			window.setMouseCursorVisible(false);
		}
		else {
			window.setMouseCursorVisible(true);
		}

		drawSelected(window, selectedPegs);

		for (auto& peg : pegs)
			window.draw(peg.getShape());

		window.display();

	}
}