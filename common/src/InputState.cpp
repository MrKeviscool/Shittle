#include "InputState.hpp"

bool InputState::m_initialised = false;
InputState InputState::m_InputState;
sf::RenderWindow* m_renderWindow = nullptr;

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
			m_keyEvents.push_back({event.key, InputState::ButtonState::pressed});
			break;
		
		case sf::Event::KeyReleased:
			m_keyEvents.push_back({event.key, InputState::ButtonState::released});
			break;

		case sf::Event::MouseMoved:
			m_mousePos = {event.mouseMove.x, event.mouseMove.y};
			break;

		case sf::Event::MouseButtonPressed:
			m_mouseEvents.push_back({ event.mouseButton, InputState::ButtonState::pressed });
			m_mouseDownOrigin = m_mousePos;
			break;
		case sf::Event::MouseButtonReleased:
			m_mouseEvents.push_back({ event.mouseButton, InputState::ButtonState::released });
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

const std::vector<InputState::KeyInfo>& InputState::keyEvents() const {
	return m_keyEvents;
}
const std::vector<InputState::MouseInfo>& InputState::mouseEvents() const {
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