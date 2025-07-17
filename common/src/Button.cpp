#include "Button.hpp"

#include "ResourceManager.hpp"

Button::Button(const sf::Vector2f size) : m_shape(size)
{

}

Button::Button(const sf::Vector2f size, const sf::Vector2f position)
    : Button(size)
{
    m_shape.setPosition(position);
}

Button::Button(const sf::Vector2f size, const sf::Vector2f position, const std::function<void()>& func)
    : m_shape(size), m_clickFunc(func)
{
    m_shape.setPosition(position);
}

Button::Button(const sf::Vector2f size, const sf::Vector2f position, const sf::Texture* texture) 
    : Button(size, position) 
{
    m_shape.setPosition(position);
    m_shape.setTexture(texture);
}

Button::Button(const sf::Vector2f size, const sf::Vector2f position, const sf::Texture* texture, const std::function<void()>& func) 
    : m_shape(size), m_clickFunc(func)
{
    m_shape.setPosition(position);
    m_shape.setTexture(texture);
}

void Button::setPosition(const sf::Vector2f pos){
    m_shape.setPosition(pos);
}

void Button::setSize(const sf::Vector2f size){
    m_shape.setSize(size);
}


void Button::setText(const std::string& text, const sf::Font* font, const unsigned int size, const float offsetAmount){
    m_text = sf::Text(text, *font, size);
    const sf::Vector2f newPos = {m_shape.getPosition().x + (m_shape.getSize().x/2) - (m_text.getGlobalBounds().width * 0.5f) , m_shape.getPosition().y + m_shape.getSize().y + offsetAmount};
    m_text.setPosition(newPos);
}

bool Button::poll(){
    if(!m_input) m_input = InputState::getPtr();

    m_hovering = (m_input->mousePos().x > m_shape.getPosition().x
        && m_input->mousePos().x < m_shape.getPosition().x + m_shape.getSize().x
        && m_input->mousePos().y > m_shape.getPosition().y
        && m_input->mousePos().y < m_shape.getPosition().y  + m_shape.getSize().y);
    
    if(!isHovering()){
        m_shape.setFillColor({ 255, 255, 255 });
        return false;
    }
    
    m_shape.setFillColor(m_tintColor);

    if(m_input->mouseEvents().find({sf::Mouse::Button::Left, InputState::ButtonState::pressed}) != m_input->mouseEvents().end()){
        if(m_clickFunc) m_clickFunc();
        return true;
    }
    return false;
}

bool Button::isHovering() const {
    return m_hovering;
}

const sf::RectangleShape& Button::getShape() const {
    return m_shape;
}

void Button::draw(sf::RenderWindow& target) const {
    target.draw(m_shape);
    target.draw(m_text);
}

void Button::setTexture(const sf::Texture* texture) {
    m_shape.setTexture(texture);
}

void Button::setFunction(const std::function<void()>& func) {
    m_clickFunc = func;
}