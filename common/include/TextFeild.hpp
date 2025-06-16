#pragma once

#include <string>

#include <SFML/Graphics.hpp>

class TextFeild {
public:

    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f position);
    
    void setFont(sf::Font* font);
    
    void setBgColor(sf::Color color);
    void setOutlineColor(sf::Color color);
    void setEmptyTextColor(sf::Color color);

    void setEmptyText(const std::string& text);
    
    void setCursorVisible(bool);

    void setWaitForEnter(bool wait);

    //returns true if text has been buffered
    bool poll();

    void display(sf::RenderWindow& window);

    const std::string& enteredText() const;

private:
    sf::RectangleShape backgroundShape;
    sf::Text text;
    sf::Font* font;
    std::string textBuffer;
    bool showCursor = true;
    bool waitForEnter = true;

};