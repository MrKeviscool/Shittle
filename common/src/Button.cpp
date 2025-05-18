#include "Button.hpp"

#include "ResourceManager.hpp"

Button::Button(const sf::Vector2f size) : m_shape(size), m_tintShape(size)
{

}

Button::Button(const sf::Vector2f size, const sf::Vector2f position)
    : Button(size)
{
    m_shape.setPosition(position);
    m_tintShape.setPosition(position);
}

Button::Button(const sf::Vector2f size, const sf::Vector2f position, std::function<void()> func)
    : m_shape(size), m_tintShape(size), m_clickFunc(func)
{
    m_shape.setPosition(position);
    m_tintShape.setPosition(position);
}

Button::Button(const sf::Vector2f size, const sf::Vector2f position, const sf::Texture* texture) 
    : Button(size, position) 
{
    m_shape.setPosition(position);
    m_tintShape.setPosition(position);
    m_shape.setTexture(texture);
}

Button::Button(const sf::Vector2f size, const sf::Vector2f position, const sf::Texture* texture, std::function<void()> func) 
    : m_shape(size), m_tintShape(size), m_clickFunc(func)
{
    m_shape.setPosition(position);
    m_tintShape.setPosition(position);
    m_shape.setTexture(texture);
}

void Button::setPosition(const sf::Vector2f pos){
    m_shape.setPosition(pos);
    m_tintShape.setPosition(pos);
}

void Button::setSize(const sf::Vector2f size){
    m_shape.setSize(size);
    m_tintShape.setSize(size);
}

void Button::setText(const std::string& text, const sf::Font* font, const float size, const float offsetAmount){
    m_text = sf::Text(text, *font, size);
    const sf::Vector2f newPos = {m_shape.getPosition().x + (m_shape.getSize().x/2) - (m_text.getGlobalBounds().width * 0.5f) , m_shape.getPosition().y + m_shape.getSize().y + offsetAmount};
    m_text.setPosition(newPos);
}

bool Button::poll(){
    if(!m_input) m_input = InputState::getPtr();

    m_hovering = (m_input->mousePos.x > m_shape.getPosition().x
        && m_input->mousePos.x < m_shape.getPosition().x + m_shape.getSize().x
        && m_input->mousePos.y > m_shape.getPosition().y
        && m_input->mousePos.y < m_shape.getPosition().y  + m_shape.getSize().y);
    
    if(!isHovering()){
        m_tintShape.setFillColor({0,0,0,0});
        return false;
    }

    m_tintShape.setFillColor(tintColor);

    for(auto& event : m_input->mouseEvents){
        if(event.event.button == sf::Mouse::Button::Left &&
            event.buttonState == InputState::ButtonState::released)
        {
            if (m_clickFunc) m_clickFunc();
            return true;
        }
    }

    return false;

}

inline bool Button::isHovering() const {
    return m_hovering;
}

sf::RectangleShape& Button::getShape() {
    return m_shape;
}

const sf::RectangleShape& Button::getTintShape() const {
    return m_tintShape;
}

void Button::draw(sf::RenderTarget& target) const {
    target.draw(m_shape);
    target.draw(m_tintShape);
    target.draw(m_text);
}

void Button::setTexture(const sf::Texture* texture) {
    m_shape.setTexture(texture);
}

void Button::setFunction(std::function<void()> func) {
    m_clickFunc = func;
}