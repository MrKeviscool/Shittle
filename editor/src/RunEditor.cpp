#include "RunEditor.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <chrono>
#include <forward_list>
#include <unordered_set>
#include <cmath>

#include "Button.hpp"
#include "InputState.hpp"
#include "ResourceManager.hpp"
#include "CursorType.hpp"
#include "Algorithms.hpp"

enum class MouseState : uint8_t {
	None,
	Selecting,
	Dragging,
};

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
			if (event.key == sf::Keyboard::Escape
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

void placePeg(const InputState& input, const CursorType& cursorType, std::forward_list<Peg>& pegs) {
	pegs.emplace_front(cursorType.peg);
}

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

std::vector<Peg*> getPegsOnMouse(const InputState& input, std::forward_list<Peg>& pegs){
	std::vector<Peg*> out;
	for(auto& peg : pegs){
		if(peg.contains({ static_cast<float>(input.mousePos().x), static_cast<float>(input.mousePos().y) }))
			out.push_back(&peg);
	}
	return out;
}

Peg* getSelectedOnMouse(const InputState& input, std::unordered_set<Peg*>& selectedPegs){
	for(auto peg : selectedPegs){
		if(peg->contains({ static_cast<float>(input.mousePos().x), static_cast<float>(input.mousePos().y) }))
			return peg;
	}
	return nullptr;
}

Peg* getPegAtPosition(const sf::Vector2f pos, std::forward_list<Peg>& pegs){
	for(auto& peg : pegs)
		if(peg.contains(pos)) return &peg;
	return nullptr;
}

Peg* getPegAtPosition(const sf::Vector2i pos, std::forward_list<Peg>& pegs) {
	const sf::Vector2f floatPos{ static_cast<float>(pos.x), static_cast<float>(pos.y) };
	for (auto& peg : pegs)
		if (peg.contains(floatPos)) return &peg;
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

void moveSelected(const sf::Vector2f amountToMove, std::unordered_set<Peg*>& selectedPegs){
	for(Peg* pegPtr : selectedPegs){
		pegPtr->getShape().move(amountToMove);
	}
}

void moveSelected(const sf::Vector2i amountToMove, std::unordered_set<Peg*>& selectedPegs) {
	moveSelected(sf::Vector2f{static_cast<float>(amountToMove.x), static_cast<float>(amountToMove.y)}, selectedPegs);
}

void exitCheck(sf::RenderWindow& window, InputState& input, ResourceManager& resources) {
	if(input.shouldClose()){
		if(askToExit(window, input, resources)){
			window.close();
		}
		return;
	}
	for (auto& keyEvnt : input.keyEvents()) {
		if (keyEvnt.key == sf::Keyboard::Escape
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
bool pollButtons(std::unordered_map<ButtonType, Button>& buttons) {
	bool out = false;
	for (auto& butt : buttons) {
		butt.second.poll();
		out = out || butt.second.isHovering();
	}
	return out;
}

void selectBox(const sf::Vector2i origin, const sf::Vector2i curMousePos, sf::RenderWindow& window, std::forward_list<Peg>& pegs, std::unordered_set<Peg*>& selectedPegs){
	sf::RectangleShape selectShape;

	selectShape.setFillColor({0, 0, 255, 127});
	selectShape.setPosition({static_cast<float>(origin.x), static_cast<float>(origin.y)});
	if(curMousePos.x < origin.x){
		selectShape.setSize({static_cast<float>(origin.x - curMousePos.x), selectShape.getSize().y});
		selectShape.setPosition(static_cast<float>(curMousePos.x), selectShape.getPosition().y);
	}
	else {
		selectShape.setSize({static_cast<float>(curMousePos.x - origin.x), selectShape.getSize().y});
	}
	if(static_cast<float>(curMousePos.y) < origin.y){
		selectShape.setSize({selectShape.getSize().x, static_cast<float>(origin.y - curMousePos.y)});
		selectShape.setPosition(selectShape.getPosition().x, static_cast<float>(curMousePos.y));
	}
	else {
		selectShape.setSize({selectShape.getSize().x, static_cast<float>(curMousePos.y - origin.y)});
	}

	window.draw(selectShape);

	const sf::Vector2f startPos = selectShape.getPosition();
	const sf::Vector2f endPos = selectShape.getPosition() + selectShape.getSize();

	for(auto& peg : pegs){
		const sf::Vector2f pegPos = peg.getShape().getPosition();
		const sf::Vector2f endPegPos = pegPos + peg.getSize();

		if(startPos.x <= endPegPos.x && endPos.x >= pegPos.x
		&& startPos.y <= endPegPos.y && endPos.y >= pegPos.y){
			selectedPegs.insert(&peg);
		}
	}

}

void resizeInPlace(Peg* peg, const int resizeSteps) {
	const sf::Vector2f originalSize = peg->getSize();

	if (peg->getShapeType() == PegShape::Circle) {

		const sf::Vector2f newSize = {
			originalSize.x * std::pow(1.1f, static_cast<float>(resizeSteps)),
			0
		};

		const float moveAmount = (originalSize.x - newSize.x) / 2;

		peg->setSize(newSize);
		peg->getShape().move(moveAmount, moveAmount);
	}
	else {
		const sf::Vector2f newSize = {
			originalSize.x * std::pow(1.1f, static_cast<float>(resizeSteps)),
			originalSize.y * std::pow(1.1f, static_cast<float>(resizeSteps)),
		};

		const sf::Vector2f moveAmount = { (originalSize.x - newSize.x) / 2, (originalSize.y - newSize.y) / 2 };
		peg->setSize(newSize);
		peg->getShape().move(moveAmount);
	}
}

void resizeSelected(const int delta, std::unordered_set<Peg*>& selectedPegs){
	for(auto pegPtr : selectedPegs){
		resizeInPlace(pegPtr, delta);
	}
}

void resizeCursor(const int delta, CursorType& cursorType){
	const sf::Vector2f curSize = cursorType.peg.getSize();
	const sf::Vector2f newSize = {
		curSize.x * std::pow(1.1f, static_cast<float>(delta)),
		((cursorType.peg.getShapeType() == PegShape::Rect)? curSize.y * std::pow(1.1f, static_cast<float>(delta)) : 0),
	};
	cursorType.peg.setSize(newSize);
}

MouseState getMouseState(const CursorType& cursorType, const InputState& input, std::forward_list<Peg>& pegs, std::unordered_set<Peg*>& selectedPegs){
	if(!cursorType.isCursor) return MouseState::None;
	
	Peg* pegUnderCursor = getPegOnMouse(input, pegs);
	if(pegUnderCursor && selectedPegs.find(pegUnderCursor) != selectedPegs.end()) 
		return MouseState::Dragging;
	
	return MouseState::Selecting;	
}

bool shouldUpdateMouseState(const InputState& input){
	return input.mouseEvents().find({sf::Mouse::Left, InputState::ButtonState::pressed}) != input.mouseEvents().end();
}

void rotateSelected(const int delta, std::unordered_set<Peg*>& selectedPegs){
	for(auto pegPtr : selectedPegs){
		pegPtr->getShape().rotate(5 * delta); //not bothered to do the math that aligns it rn
	}
}

void rotateCursor(){

}

void rotateOrScale(const MouseState mouseState, const InputState& input, CursorType& cursorType, std::unordered_set<Peg*>& selectedPegs){
	if(input.mouseScrollDelta() != 0){
		const bool ctrlPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);

		if(mouseState == MouseState::None && !ctrlPressed){
			resizeCursor(input.mouseScrollDelta(), cursorType);
		}
		else if(!ctrlPressed){
			resizeSelected(input.mouseScrollDelta(), selectedPegs);
		}
		else if(mouseState == MouseState::None) {
			rotateCursor();
		}
		else{
			rotateSelected(input.mouseScrollDelta(), selectedPegs);
		}
	}
}

void handleMouseEvents(const MouseState mouseState, CursorType& cursorType, sf::RenderWindow& window, InputState& input, std::forward_list<Peg>& pegs, std::unordered_set<Peg*>& selectedPegs) {
	const bool mouseIsDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	
	rotateOrScale(mouseState, input, cursorType, selectedPegs);
	
	if(mouseState == MouseState::Selecting && mouseIsDown && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		deselectAll(selectedPegs);

	if(mouseState == MouseState::None 
		&& input.mouseEvents().find({sf::Mouse::Left, InputState::ButtonState::released}) != input.mouseEvents().end()){
		placePeg(input, cursorType, pegs);
		return;
	}
	if(mouseState == MouseState::Selecting && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		selectBox(input.mouseDownOrigin(), input.mousePos(), window, pegs, selectedPegs);
		return;
	}

	if(mouseState == MouseState::Dragging && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		moveSelected(input.mouseMoveAmount(), selectedPegs);
		return;
	}
}

void runEditor(sf::RenderWindow& window, InputState& input, ResourceManager& resources, std::unordered_map<ButtonType, Button>& buttons) {
	CursorType cursorType;
	MouseState mouseState = MouseState::None;
	std::forward_list<Peg> pegs;
	std::unordered_set<Peg*> selectedPegs;

	buttons[ButtonType::cursorPeg].   setFunction([&cursorType](){cursorType = CursorType(Peg(PegShape::Circle), false);});
	buttons[ButtonType::cursorBrick]. setFunction([&cursorType](){cursorType = CursorType(Peg(PegShape::Rect), false);});
	buttons[ButtonType::cursorSelect].setFunction([&cursorType](){cursorType.isCursor = true;});

	while (window.isOpen()) {
		input.pollEvents();

		exitCheck(window, input, resources);

		const bool buttonIsHovered = pollButtons(buttons);

		if(shouldUpdateMouseState(input)){
			mouseState = getMouseState(cursorType, input, pegs, selectedPegs);
		}

		if(!buttonIsHovered){
			handleMouseEvents(mouseState, cursorType, window, input, pegs, selectedPegs);
		}

		drawCursorType(window, buttonIsHovered, input.mousePos(), cursorType);
		drawSelected(window, selectedPegs);

		drawPegs(window, pegs);

		drawButtons(window, buttons);

		window.display();
		window.clear();
	}
}