#include "TextField.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

#include "InputState.hpp"

TextField::TextField(InputState& input, const sf::Font& font) : input(input){
    text.setFont(font);
}

void TextField::setFont(const sf::Font& font){
    text.setFont(font);
}

void TextField::setBgColor(const sf::Color color){
    backgroundShape.setFillColor(color);
}

bool TextField::isFocused() const {
    return m_isFocused;
}

void TextField::setPosition(sf::Vector2f position){
    backgroundShape.setPosition(position);
    text.setPosition(position);
}

void TextField::setSize(sf::Vector2f size){
    backgroundShape.setSize(size);
}

static bool rectContains(const sf::Vector2f start, const sf::Vector2f end, const sf::Vector2f point){
    return (start.x > point.x && end.x < point.x &&
            start.y > point.y && end.y < point.y);
}

static bool focusCheck(const InputState& input, const sf::RectangleShape& backgroundShape){
    return rectContains(backgroundShape.getPosition(),
        backgroundShape.getPosition() + backgroundShape.getSize(),
        {static_cast<float>(input.mousePos().x), static_cast<float>(input.mousePos().y)});
}

void TextField::poll(){
    if(input.mouseEventsContains({sf::Mouse::Button::Left, InputState::ButtonState::pressed}))
        m_isFocused = focusCheck(input, backgroundShape);

    if(!m_isFocused){
        backgroundShape.setFillColor(bgColor);
        return;
    }
    
    backgroundShape.setFillColor(bgColor * selectedDarkness);

    for(auto& key : input.keyEvents()){ //loop keys and wait for enter
        textBuffer.insert(textBuffer.cend(), input.textEntered().cbegin(), input.textEntered().cend());
        text.setString(textBuffer);
        if(key.key == sf::Keyboard::Enter) m_isFocused = false;
    }
}

void TextField::display(sf::RenderWindow& window){
    window.draw(backgroundShape);
    window.draw(text); 
}
