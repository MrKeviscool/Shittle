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
    mouseEvents.clear();
    keyEvents.clear();
}

void InputState::pollEvents(){

	reset();

	sf::Event event;

	while (m_renderWindow->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			m_renderWindow->close();
			break;

		case sf::Event::KeyPressed:
			keyEvents.push_back({event.key, InputState::ButtonState::pressed});
			break;
		
		case sf::Event::KeyReleased:
			keyEvents.push_back({event.key, InputState::ButtonState::released});
			break;

		case sf::Event::MouseMoved:
			mousePos = {event.mouseMove.x, event.mouseMove.y};
			break;

		case sf::Event::MouseButtonPressed:
			mouseEvents.push_back({ event.mouseButton, InputState::ButtonState::pressed });
				break;
		case sf::Event::MouseButtonReleased:
			mouseEvents.push_back({ event.mouseButton, InputState::ButtonState::released });
			break;
		default:
			continue;
		}

	}

}