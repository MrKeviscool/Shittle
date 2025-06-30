#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "InputState.hpp"
#include "MulColor.hpp"

class TextField {
public:
    TextField(InputState& input, const sf::Font& font, const std::string& emptyFieldText = "", bool keepText = true);

    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f position);
    void setFont(const sf::Font& font);
    void setBgColor(sf::Color color);
    void setOutlineColor(sf::Color color);
    void setEmptyTextColor(sf::Color color);
    void setEmptyText(const std::string& text);
    void setCursorVisible(bool);
    void setWaitForEnter(bool wait);
    void setSelectedBrightnessMult(float multiplier);
    void poll();
    void display(sf::RenderWindow& window);
    const std::string& enteredText() const;
    bool isFocused() const;

private:
    sf::RectangleShape backgroundShape;
    sf::Text text;
    std::string textBuffer;
    std::string emptyText;
    std::string m_enteredText;
    InputState& input;

    float selectedBrightnessMul = 0.7f;
    const MulColor bgColor {127, 127, 127};

    bool showCursor = true;
    bool waitForEnter = true;
    bool m_isFocused = false;
    bool keepText = true;

    void updateFocus();
    void setFocus(bool focused);
};
