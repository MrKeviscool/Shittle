#include "TextFeild.hpp"
#include "InputState.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <type_traits>

TextFeild::TextFeild(InputState& input) : input(input){

}

void TextFeild::setFont(const sf::Font* _font){
    font = _font; 
}

void TextFeild::setBgColor(const sf::Color color){
    backgroundShape.setFillColor(color);
}

bool TextFeild::isFocused() const {
    return m_isFocused;
}

static bool rectContains(const sf::Vector2f start, const sf::Vector2f end, const sf::Vector2f point){
    return (start.x > point.x && end.x < point.x &&
            start.y > point.y && end.y < point.y);
}

void TextFeild::poll(){
    if(input.mouseEventsContains({sf::Mouse::Left, InputState::ButtonState::pressed})){
        if(rectContains(backgroundShape.getPosition(),
            backgroundShape.getPosition() + backgroundShape.getSize(),
            {static_cast<float>(input.mousePos().x), static_cast<float>(input.mousePos().y)})
        ){
            m_isFocused = true;          
        }
        else m_isFocused = false;
    }
    if(!m_isFocused) return;
}
