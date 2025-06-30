#include "TextField.hpp"
#include "InputState.hpp"

TextField::TextField(InputState& input, const sf::Font& font, const std::string& emptyFieldText, const bool keepText)
    : emptyText(emptyFieldText), input(input), keepText(keepText)
{
    text.setFont(font);
    text.setString(emptyText);
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
    const sf::Vector2f textPosition = {position.x, position.y - (text.getCharacterSize()/4.f)};
    text.setPosition(textPosition);
}

void TextField::setSize(const sf::Vector2f size){
    backgroundShape.setSize(size);
    text.setCharacterSize(static_cast<const unsigned int>(size.y));
}

static bool rectContains(const sf::Vector2f start, const sf::Vector2f end, const sf::Vector2f point){
    return (start.x > point.x && end.x < point.x &&
            start.y > point.y && end.y < point.y);
}

void TextField::setEmptyText(const std::string& str){
    emptyText = str;
}

enum class ClickPos : uint8_t {
    DidntClick,
    On,
    Off,
};

static bool mouseInBounds(const InputState& input, const sf::FloatRect& bounds){
    return bounds.contains({static_cast<float>(input.mousePos().x), static_cast<float>(input.mousePos().y)});
}

static bool clickedMouse(const InputState& input) {
    return input.mouseEventsContains({sf::Mouse::Button::Left, InputState::ButtonState::pressed});
}

void TextField::updateFocus() {
    const bool clicked = clickedMouse(input);
    if(!clicked) return;
    const bool hovering = mouseInBounds(input, backgroundShape.getGlobalBounds());
    setFocus(hovering);
}

void TextField::setFocus(const bool focused){
    if(focused && !m_isFocused){
        backgroundShape.setFillColor(bgColor * selectedDarkness);
        m_isFocused = true;

    } else if (!focused && m_isFocused){
        backgroundShape.setFillColor(bgColor);
        m_isFocused = false;
    }
}

void TextField::poll(){

    updateFocus();
    if(!m_isFocused) return;

    if(input.keyEventsContains({sf::Keyboard::Key::Enter, InputState::ButtonState::pressed})){
        setFocus(false);
        if(keepText) m_enteredText = textBuffer;
        else {
            std::swap(m_enteredText, textBuffer); //keeps textBuffer in a valid state
            textBuffer.clear();
        }
    }

    if(input.textEntered().empty()) return;

    const auto readCheck = [this](const char c) -> bool {
        const char ASCII_PRINT_START = 32;
        if(c == '\b'){
            if(!this->textBuffer.empty()) this->textBuffer.pop_back();
            return false;
        }
        return c > ASCII_PRINT_START-1;
    };

    std::copy_if(input.textEntered().cbegin(), input.textEntered().cend(), std::back_inserter(textBuffer), readCheck);
    if(textBuffer.empty()) text.setString(emptyText);
    else text.setString(textBuffer);
}

void TextField::display(sf::RenderWindow& window){
    window.draw(backgroundShape);
    window.draw(text); 
}

const std::string& TextField::enteredText() const {
    return m_enteredText; 
}
