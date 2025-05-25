#include "RunEditor.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <chrono>
#include <iostream>
#include <forward_list>
#include <unordered_set>

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
		for (auto& event : input.keyEvents()) {
			if (event.event.code == sf::Keyboard::Escape
				&& event.buttonState == InputState::ButtonState::released)
			{
				return false;
			}
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

	for(auto iter = input.mouseEvents().begin(); iter != input.mouseEvents().end(); iter++){
		if (iter == input.mouseEvents().end() - 1 && iter->buttonState != InputState::ButtonState::pressed && iter->event.button != sf::Mouse::Left) {
			std::cout << "no button press found\n";
			return false;
		}
	}

	auto startTime = std::chrono::steady_clock::now();
	while(std::chrono::steady_clock::now() - startTime < maxClickLength){
		input.pollEvents();
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			return false;
	}
	return true;
};

void deselectAll(std::unordered_set<Peg*>& selectedPegs){
	selectedPegs.clear();
}

Peg* getPegOnMouse(const InputState& input, std::forward_list<Peg>& pegs){
	for(auto& peg : pegs){
		if(peg.contains({ static_cast<float>(input.mousePos().x), static_cast<float>(input.mousePos().y) }))
			return &peg;
	}
	return nullptr;
}

bool isSelected(const std::unordered_set<Peg*>& selectedPegs, Peg* peg){
	return selectedPegs.find(peg) != selectedPegs.end();
}

void togglePegSelect(const InputState& input, Peg* peg, std::unordered_set<Peg*>& selectedPegs){
	if(!peg) return;

	if (selectedPegs.find(peg) == selectedPegs.end())
		selectedPegs.emplace(peg);
	else
		selectedPegs.erase(peg);
}

void drawButtons(sf::RenderTarget& target, const std::unordered_map<std::string, Button>& buttons) {
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

void drawSelected(sf::RenderTarget& window, const std::unordered_set<Peg*>& selectedPegs) {
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

			shapeToDraw.setPosition(shape->getPosition() - (shape->getSize() / 4.0f));
			shapeToDraw.setFillColor(sf::Color::Yellow);
			window.draw(shapeToDraw);
		}
	}
}

void moveSelected(sf::RenderWindow& window, InputState& input, const sf::Vector2f mouseOrigin, std::forward_list<Peg>& pegs, const std::unordered_map<std::string, Button>& buttons, std::unordered_set<Peg*>& selected) {

	sf::Vector2f lastMousePos = mouseOrigin;

	while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		drawSelected(window, selected);
		drawPegs(window, pegs);
		drawButtons(window, buttons);
		input.pollEvents();
		window.display();
		window.clear();

		const sf::Vector2f curMousePos = {static_cast<float>(input.mousePos().x), static_cast<float>(input.mousePos().y)};

		for(auto pegPtr : selected)
			pegPtr->getShape().move(curMousePos - lastMousePos);
		
		lastMousePos = curMousePos;

	}
}

void exitCheck(sf::RenderWindow& window, InputState& input, ResourceManager& resources) {
	if(input.shouldClose()){
		if(askToExit(window, input, resources)){
			window.close();
		}
		return;
	}
	for (auto& keyEvnt : input.keyEvents()) {
		if (keyEvnt.event.code == sf::Keyboard::Escape
			&& keyEvnt.buttonState == InputState::ButtonState::released)
		{
			if(askToExit(window, input, resources)){
				window.close();
			}
			return;
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

void selectBox(const sf::Vector2f origin, sf::RenderWindow& window, InputState& input, std::forward_list<Peg>& pegs, std::unordered_set<Peg*>& selectedPegs, std::unordered_map<std::string, Button>& buttons){
	sf::RectangleShape selectShape;
	selectShape.setFillColor({0, 0, 255, 127});
	selectShape.setPosition(origin);
	while(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		input.pollEvents();
		window.clear();
		drawSelected(window, selectedPegs);
		drawPegs(window, pegs);
		drawButtons(window, buttons);
		window.draw(selectShape);
		window.display();

		if(static_cast<float>(input.mousePos().x) <  origin.x){
			selectShape.setSize({origin.x - static_cast<float>(input.mousePos().x), selectShape.getSize().y});
			selectShape.setPosition(static_cast<float>(input.mousePos().x), selectShape.getPosition().y);
		}
		else {
			selectShape.setSize({static_cast<float>(input.mousePos().x) - origin.x, selectShape.getSize().y});
		}
		if(static_cast<float>(input.mousePos().y) < origin.y){
			selectShape.setSize({selectShape.getSize().x, origin.y - static_cast<float>(input.mousePos().y)});
			selectShape.setPosition(selectShape.getPosition().x, static_cast<float>(input.mousePos().y));
		}
		else {
			selectShape.setSize({selectShape.getSize().x, static_cast<float>(input.mousePos().y) - origin.y});
		}
	}

	const sf::Vector2f startPos = selectShape.getPosition();
	const sf::Vector2f endPos = selectShape.getPosition() + selectShape.getSize();

	for(auto& peg : pegs){
		const sf::Vector2f pegPos = peg.getShape().getPosition();

		if(pegPos.x > startPos.x && pegPos.x < endPos.x && pegPos.y > startPos.y && pegPos.y < endPos.y)
			selectedPegs.insert(&peg);
	}

}

void handleMouseEvents(const CursorType& cursorType, sf::RenderWindow& window, InputState& input, std::forward_list<Peg>& pegs, std::unordered_set<Peg*>& selectedPegs, std::unordered_map<std::string, Button>& buttons) {
	for (auto& mouseEvnt : input.mouseEvents()) {
		if (mouseEvnt.event.button != sf::Mouse::Left || mouseEvnt.buttonState != InputState::ButtonState::pressed)
			continue;
			
		if (!cursorType.isCursor){
			placePeg(input, cursorType, pegs);
			return;
		}

		const sf::Vector2f mousePos = {static_cast<float>(input.mousePos().x), static_cast<float>(input.mousePos().y)};
		Peg* pegUnderCursor = getPegOnMouse(input, pegs);
		bool mouseWasHeld = heldMouse(input);

		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
			deselectAll(selectedPegs);
		}

		if(!pegUnderCursor){
			selectBox(mousePos, window, input, pegs, selectedPegs, buttons);
			return;
		}

		if (!mouseWasHeld) {
			togglePegSelect(input, pegUnderCursor, selectedPegs);
			return;
		}

		if(isSelected(selectedPegs, pegUnderCursor)){
			moveSelected(window, input, mousePos, pegs, buttons, selectedPegs);
			return;
		}
	}
}

void runEditor(sf::RenderWindow& window, InputState& input, ResourceManager& resources, std::unordered_map<std::string, Button>& buttons) {
	CursorType cursorType;

	buttons["cursorPeg"].   setFunction([&cursorType](){cursorType = CursorType(Peg(PegShape::Circle), false);});
	buttons["cursorBrick"]. setFunction([&cursorType](){cursorType = CursorType(Peg(PegShape::Rect), false);	});
	buttons["cursorSelect"].setFunction([&cursorType](){cursorType = CursorType(cursorType.peg, true);		});

	std::forward_list<Peg> pegs;
	std::unordered_set<Peg*> selectedPegs;

	while (window.isOpen()) {
		input.pollEvents();

		exitCheck(window, input, resources);

		const bool buttonIsHovered = pollButtons(buttons);
		if(!buttonIsHovered)
			handleMouseEvents(cursorType, window, input, pegs, selectedPegs, buttons);

		drawCursorType(window, buttonIsHovered, input.mousePos(), cursorType);
		drawSelected(window, selectedPegs);

		drawPegs(window, pegs);

		drawButtons(window, buttons);

		window.display();
		window.clear();
	}
}