#include "InputState.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include <utility>
#include <chrono>

bool InputState::m_initialised = false;
InputState InputState::m_InputState;
sf::RenderWindow* m_renderWindow = nullptr;

size_t InputState::hash::operator()(const KeyInfo& toHash) const noexcept {
	constexpr const int bitsInByte = 8;
	return (static_cast<size_t>(toHash.key) | (static_cast<size_t>(toHash.buttonState) << ((sizeof(size_t) * bitsInByte) - sizeof(decltype(toHash.buttonState)) * bitsInByte)));
}

size_t InputState::hash::operator()(const MouseInfo& toHash) const noexcept {
	constexpr const int bitsInByte = 8;
	return (static_cast<size_t>(toHash.button) | (static_cast<size_t>(toHash.buttonState) << ((sizeof(size_t) * bitsInByte) - sizeof(decltype(toHash.buttonState)) * bitsInByte)));
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
	m_textEntered.clear();
	m_resisedWindow = false;
	m_shouldClose = false;
	m_mouseMoveAmount = {0,0};
	m_mouseScrollDelta = 0;
	m_doubleClicked = false;
}

void InputState::pollEvents(){
	reset();
	const sf::Vector2i oldMousePos = m_mousePos;
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
			m_mousePos = {
			   static_cast<int>(std::roundf((static_cast<float>(event.mouseMove.x) - m_mousePixelOffset.x) * m_mousePixelScale.x)),
			   static_cast<int>(std::roundf((static_cast<float>(event.mouseMove.y) - m_mousePixelOffset.y) * m_mousePixelScale.y)),
			};
			break;
		case sf::Event::MouseButtonPressed:
			m_mouseEvents.insert({ event.mouseButton.button, InputState::ButtonState::pressed });
			m_mouseDownOrigin = m_mousePos;
			m_doubleClickCheck(event);
			break;
		case sf::Event::MouseButtonReleased:
			m_mouseEvents.insert({ event.mouseButton.button, InputState::ButtonState::released });
			break;
		case sf::Event::TextEntered:
			m_textEntered.push_back(static_cast<char>(event.text.unicode));
		case sf::Event::Resized:
			m_resisedWindow = true;
			m_windowSize = m_renderWindow->getSize();
			break;
		case sf::Event::MouseWheelScrolled:
			m_mouseScrollDelta += static_cast<int>(std::roundf(event.mouseWheelScroll.delta));
			break;
		default:
			continue;
		}
	}
	m_mouseMoveAmount = m_mousePos - oldMousePos;
}

void InputState::m_doubleClickCheck(const sf::Event& event){
	if(event.mouseButton.button != sf::Mouse::Button::Left) return;
	const auto now = std::chrono::steady_clock::now();
	const auto duration = now - m_lastClickTime;
	m_doubleClicked = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() < m_doubleClickMs;
	m_lastClickTime = now; 
}

void InputState::setDoubleClickMs(const int ms){
	m_doubleClickMs = ms;
}

void InputState::setBaseMouseOffset(const sf::Vector2f offset){
	m_mousePixelOffset = offset;
}
void InputState::setMouseScale(const sf::Vector2f scale){
	m_mousePixelScale = scale;
}

const std::unordered_set<InputState::KeyInfo, InputState::hash>& InputState::keyEvents() const {
	return m_keyEvents;
}
const std::unordered_set<InputState::MouseInfo, InputState::hash>& InputState::mouseEvents() const {
	return m_mouseEvents;
};
const std::vector<char>& InputState::textEntered() const {
	return m_textEntered;
}

bool InputState::keyEventsContains(const InputState::KeyInfo info) const {
	return m_keyEvents.find(info) != m_keyEvents.end();
}

bool InputState::mouseEventsContains(const InputState::MouseInfo info) const {
	return m_mouseEvents.find(info) != m_mouseEvents.end();
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
sf::Vector2i InputState::mouseMoveAmount() const {
	return m_mouseMoveAmount;
}
int InputState::mouseScrollDelta() const {
	return m_mouseScrollDelta;
}
bool InputState::resisedWindow() const {
	return m_resisedWindow;
}
bool InputState::shouldClose() const {
	return m_shouldClose;
}

bool InputState::doubleClicked() const {
	return m_doubleClicked;
};
