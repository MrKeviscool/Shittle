#include "InputState.hpp"

bool InputState::m_initialised = false;
InputState InputState::m_InputState;
sf::RenderWindow* m_renderWindow = nullptr;

size_t InputState::hash::operator()(const KeyInfo& toHash) const noexcept {
	return (static_cast<size_t>(toHash.key) | (static_cast<size_t>(toHash.buttonState) << ((sizeof(size_t) * 8) - sizeof(decltype(toHash.buttonState)) * 8)));
}

size_t InputState::hash::operator()(const MouseInfo& toHash) const noexcept {
	return (static_cast<size_t>(toHash.button) | (static_cast<size_t>(toHash.buttonState) << ((sizeof(size_t) * 8) - sizeof(decltype(toHash.buttonState)) * 8)));
};

bool InputState::KeyInfo::operator==(const InputState::KeyInfo& other) const noexcept {
	return key == other.key
		&& buttonState == other.buttonState; 
}

bool InputState::MouseInfo::operator==(const InputState::MouseInfo& other) const noexcept {
	return button == other.button
		&& buttonState == other.buttonState; 
}

InputState* InputState::getPtr() {
    if (!m_initialised) throw std::exception();
    return &m_InputState;
}

InputState& InputState::getRef(){
    if (!m_initialised) throw std::exception();
    return m_InputState;
}

void InputState::initalise(sf::RenderWindow* window) {
    m_InputState.m_renderWindow = window;
    m_initialised = true;
}

bool InputState::isInitalised() {
	return m_initialised;
}

void InputState::reset(){
    m_mouseEvents.clear();
    m_keyEvents.clear();
	m_resisedWindow = false;
	m_shouldClose = false;
}

void InputState::pollEvents(){

	reset();

	sf::Event event;

	while (m_renderWindow->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			m_shouldClose = true;
			break;
		case sf::Event::KeyPressed:
			m_keyEvents.insert({event.key.code, InputState::ButtonState::pressed});
			break;
		
		case sf::Event::KeyReleased:
			m_keyEvents.insert({event.key.code, InputState::ButtonState::released});
			break;

		case sf::Event::MouseMoved:
			m_mousePos = {event.mouseMove.x, event.mouseMove.y};
			break;

		case sf::Event::MouseButtonPressed:
			m_mouseEvents.insert({ event.mouseButton.button, InputState::ButtonState::pressed });
			m_mouseDownOrigin = m_mousePos;
			break;
		case sf::Event::MouseButtonReleased:
			m_mouseEvents.insert({ event.mouseButton.button, InputState::ButtonState::released });
			break;
		case sf::Event::Resized:
			m_resisedWindow = true;
			m_windowSize = m_renderWindow->getSize();
			break;
		default:
			continue;
		}

	}

}

const std::unordered_set<InputState::KeyInfo, InputState::hash>& InputState::keyEvents() const {
	return m_keyEvents;
}
const std::unordered_set<InputState::MouseInfo, InputState::hash>& InputState::mouseEvents() const {
	return m_mouseEvents;
}
sf::Vector2u InputState::windowSize() const {
	return m_windowSize;
}
sf::Vector2i InputState::mousePos() const {
	return m_mousePos;
}

sf::Vector2i InputState::mouseDownOrigin() const {
	return m_mouseDownOrigin;
}

bool InputState::resisedWindow() const {
	return m_resisedWindow;
}
bool InputState::shouldClose() const {
	return m_shouldClose;
}