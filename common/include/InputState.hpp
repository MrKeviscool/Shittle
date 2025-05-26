#pragma once

#include <exception>
#include <vector>

#include <SFML/Graphics.hpp>

class InputState {
public:
    static InputState* getPtr();
    static InputState& getRef();
    static bool isInitalised();

    static void initalise(sf::RenderWindow* window);

    enum class ButtonState : uint8_t{
        pressed,
        released,
    };

    struct MouseInfo {
        sf::Event::MouseButtonEvent event;
        ButtonState buttonState;
    };

    struct KeyInfo {
        sf::Event::KeyEvent event;
        ButtonState buttonState;
    };


    const std::vector<KeyInfo>& keyEvents() const;
    const std::vector<MouseInfo>& mouseEvents() const;
    sf::Vector2u windowSize() const;
    sf::Vector2i mousePos() const;
    sf::Vector2i mouseDownOrigin() const;

    bool resisedWindow() const;
    bool shouldClose() const;

    void reset();
    void pollEvents();

private:
    static bool m_initialised;
    static InputState m_InputState;
    sf::RenderWindow* m_renderWindow;

    std::vector<KeyInfo> m_keyEvents;
    std::vector<MouseInfo> m_mouseEvents;
    sf::Vector2i m_mousePos;
    sf::Vector2i m_mouseDownOrigin;
    sf::Vector2u m_windowSize;
    
    bool m_resisedWindow;
    bool m_shouldClose;

    InputState() = default;
    InputState(const InputState&) = delete;
    InputState(InputState&&) = delete;

};