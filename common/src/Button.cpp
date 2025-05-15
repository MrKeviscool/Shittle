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

Button::Button(const sf::Vector2f size, const sf::Vector2f position, std::string textureName) 
    : Button(size, position) 
{
    m_shape.setPosition(position);
    m_tintShape.setPosition(position);
    m_shape.setTexture(static_cast<const sf::Texture*>(ResourceManager::getRef().getResource(textureName)));
}

Button::Button(const sf::Vector2f size, const sf::Vector2f position, std::string textureName, std::function<void()> func) 
    : m_shape(size), m_tintShape(size), m_clickFunc(func)
{
    m_shape.setPosition(position);
    m_tintShape.setPosition(position);
    m_shape.setTexture(static_cast<const sf::Texture*>(ResourceManager::getRef().getResource(textureName)));
}

void Button::setPosition(const sf::Vector2f pos){
    m_shape.setPosition(pos);
    m_tintShape.setPosition(pos);
}

void Button::setSize(const sf::Vector2f size){
    m_shape.setSize(size);
    m_tintShape.setSize(size);
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