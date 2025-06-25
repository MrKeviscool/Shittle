#pragma once

#include <exception>
#include <unordered_set>

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

    struct KeyInfo {
        sf::Keyboard::Key key;
        ButtonState buttonState;
        bool operator==(const KeyInfo& other) const noexcept;
    };
    struct MouseInfo {
        sf::Mouse::Button button;
        ButtonState buttonState;
        bool operator==(const MouseInfo& other) const noexcept;
    };

    // template<typename T>
    struct hash {
        size_t operator()(const KeyInfo& toHash) const noexcept;
        size_t operator()(const MouseInfo& toHash) const noexcept;
    };

    const std::unordered_set<KeyInfo, hash>& keyEvents() const;
    const std::unordered_set<MouseInfo, hash>& mouseEvents() const;

    bool keyEventsContains(const KeyInfo keyInfo) const;
    bool mouseEventsContains(const MouseInfo mouseInfo) const;

    sf::Vector2u windowSize() const;
    sf::Vector2i mousePos() const;
    sf::Vector2i mouseDownOrigin() const;
    sf::Vector2i mouseMoveAmount() const;
    int mouseScrollDelta() const;

    bool resisedWindow() const;
    bool shouldClose() const;

    void reset();
    void pollEvents();

private:
    static bool m_initialised;
    static InputState m_InputState;
    sf::RenderWindow* m_renderWindow = nullptr;

    std::unordered_set<KeyInfo, hash> m_keyEvents;
    std::unordered_set<MouseInfo, hash> m_mouseEvents;
    sf::Vector2i m_mousePos{ 0,0 };
    sf::Vector2i m_mouseDownOrigin{ 0,0 };
    sf::Vector2i m_mouseMoveAmount{ 0,0 };
    sf::Vector2u m_windowSize{ 0,0 };
    int m_mouseScrollDelta = 0;
    
    bool m_resisedWindow = false;
    bool m_shouldClose = false;

    InputState() = default;
    InputState(const InputState&) = delete;
    InputState(InputState&&) = delete;

};
