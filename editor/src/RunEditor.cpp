#include "RunEditor.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <chrono>
#include <iostream>
#include <forward_list>

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


	yesButton.setText("exit", textFont, 20U);
	noButton.setText("cancel", textFont, 20U);

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

void placePeg(const InputState& input, const CursorType& cursorType, std::forward_list<Peg>& pegs) {
	pegs.emplace_front(cursorType.peg);
}

bool heldMouse(InputState& input){
	const std::chrono::milliseconds maxClickLength(200);

	for(auto iter = input.mouseEvents.begin(); iter != input.mouseEvents.end(); iter++){
		if (iter == input.mouseEvents.end() - 1 && iter->buttonState != InputState::ButtonState::pressed && iter->event.button != sf::Mouse::Left) {
			std::cout << "no button press found\n";
			return false;
		}
	}

	auto startTime = std::chrono::steady_clock::now();
	while(std::chrono::steady_clock::now() - startTime < maxClickLength){
		std::cout << "time heled ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count() << '\n';
		input.pollEvents();
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			return false;
	}
	return true;
};

void selectPeg(const InputState& input, std::forward_list<Peg>& pegs, std::vector<Peg*>& selectedPegs){
	for(auto& peg : pegs){
		if(peg.contains({static_cast<float>(input.mousePos.x), static_cast<float>(input.mousePos.y)}))
			selectedPegs.push_back(&peg);
	}
}

void moveSelected(const InputState& input, const sf::Vector2f mouseOrigin, const std::vector<Peg*>& selected){
	std::cout << "move selected\n";
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

void exitCheck(sf::RenderWindow& window, InputState& input, ResourceManager& resources) {
	for (auto& keyEvnt : input.keyEvents) {
		if (keyEvnt.event.code == sf::Keyboard::Escape
			&& keyEvnt.buttonState == InputState::ButtonState::released
			&& askToExit(window, input, resources))
		{
			window.close();
		}
	}
}

//returns true if a button is hovered
bool pollButtons(std::unordered_map<std::string, Button>& buttons) {
	bool out = false;
	for (auto& butt : buttons) {
		butt.second.poll();
		out = out || butt.second.isHovering();
	}
	return out;
}

void drawButtons(sf::RenderTarget& target, std::unordered_map<std::string, Button>& buttons) {
	for (auto& butt : buttons)
		butt.second.draw(target);
}

void drawPegOrCursor(sf::RenderWindow& window, bool isButtonHovered, sf::Vector2i mousePos, CursorType& cursorType) {
	if (!cursorType.isCursor && !isButtonHovered) {
		cursorType.peg.getShape().setPosition({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) });
		window.draw(cursorType.peg.getShape());
		window.setMouseCursorVisible(false);
	}
	else 
		window.setMouseCursorVisible(true);
	
}

void drawPegs(sf::RenderWindow& window, const std::forward_list<Peg>& pegs){
	for(auto& peg : pegs)
		window.draw(peg.getShape());
}

void runEditor(sf::RenderWindow& window, InputState& input, ResourceManager& resources, std::unordered_map<std::string, Button>& buttons) {
	CursorType cursorType;

	buttons["cursorPeg"].setFunction([&cursorType]()	{cursorType = CursorType(Peg(PegShape::Circle), false); });
	buttons["cursorBrick"].setFunction([&cursorType]()  {cursorType = CursorType(Peg(PegShape::Rect), false);	});
	buttons["cursorSelect"].setFunction([&cursorType]() {cursorType = CursorType(cursorType.peg, true);			});

	std::forward_list<Peg> pegs;
	std::vector<Peg*> selectedPegs;

	while (window.isOpen()) {
		input.pollEvents();

		exitCheck(window, input, resources);

		window.clear();

		const bool buttonIsHovered = pollButtons(buttons);

		for (auto& mouseEvnt : input.mouseEvents) {
			if (!buttonIsHovered && mouseEvnt.event.button == sf::Mouse::Left && mouseEvnt.buttonState == InputState::ButtonState::released) {
				if (!cursorType.isCursor) placePeg(input, cursorType, pegs);
				else if (!heldMouse(input)) {
					selectPeg(input, pegs, selectedPegs);
				}
				else {
					moveSelected(input, { static_cast<float>(input.mousePos.x), static_cast<float>(input.mousePos.y) }, selectedPegs);
				}
			}
		}

		drawPegOrCursor(window, buttonIsHovered, input.mousePos, cursorType);
		drawSelected(window, selectedPegs);

		drawPegs(window, pegs);

		drawButtons(window, buttons);

		window.display();
		window.clear();
	}
}