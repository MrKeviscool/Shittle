#include "TextField.hpp"

TextField::TextField(InputState& input, const sf::Font& font, const std::string& emptyFieldText, const bool clearOnSubmit)
    : emptyText(emptyFieldText), input(input), clearOnSubmit(clearOnSubmit)
{
    text.setFont(font);
    text.setString(emptyText);
}

void TextField::setFont(const sf::Font& font){
    text.setFont(font);
}

void TextField::setBgColor(const sf::Color& color){
    backgroundShape.setFillColor(color);
    bgColor = color;
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

void TextField::setEmptyText(const std::string& str){
    emptyText = str;
    if(text.getString().isEmpty()) text.setString(emptyText);
}

void TextField::setSelectedBrightnessMult(const float multiplier){
    selectedBrightnessMul = multiplier;
}

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
        backgroundShape.setFillColor(bgColor * selectedBrightnessMul);
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
        submitEntered();
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

void TextField::setEnteredText(const std::string &newText){
    textBuffer = newText;
    text.setString(textBuffer);
}

void TextField::setClearOnSubmit(const bool clear){
    clearOnSubmit = clear;
}

void TextField::submitEntered(){
    if(clearOnSubmit){
        std::swap(textBuffer, m_enteredText); //keeps textBuffer in a valid state, may juyst be able to std::move
        textBuffer.clear();
    }
    else {
        m_enteredText = textBuffer;
    }
}
