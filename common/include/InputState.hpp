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

    sf::Vector2i mousePos;
    std::vector<MouseInfo> mouseEvents;


    struct KeyInfo {
        sf::Event::KeyEvent event;
        ButtonState buttonState;
    };
    std::vector<KeyInfo> keyEvents;

    void reset();
    void pollEvents();

private:
    static bool m_initialised;
    static InputState m_InputState;
    sf::RenderWindow* m_renderWindow = nullptr;

    InputState() = default;
    InputState(const InputState&) = delete;
    InputState(InputState&&) = delete;

};