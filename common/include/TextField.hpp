#pragma once

#include "InputState.hpp"

#include <string>

#include <SFML/Graphics.hpp>

#include "MulColor.hpp"

class TextField {
public:
    TextField(InputState& input, const sf::Font& font);

    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f position);
    
    void setFont(const sf::Font& font);
    
    void setBgColor(sf::Color color);
    void setOutlineColor(sf::Color color);
    void setEmptyTextColor(sf::Color color);

    void setEmptyText(const std::string& text);
    
    void setCursorVisible(bool);

    void setWaitForEnter(bool wait);

    void poll();

    void display(sf::RenderWindow& window);

    const std::string& enteredText() const;
    bool isFocused() const;

private:
    sf::RectangleShape backgroundShape;
    sf::Text text;
    std::string textBuffer;
    InputState& input;

    float selectedDarkness = 0.7f;
    MulColor bgColor {127, 127, 127};

    bool showCursor = true;
    bool waitForEnter = true;
    bool m_isFocused = false;

};
