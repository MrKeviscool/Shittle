#pragma once

#include "InputState.hpp"

#include <functional>

#include <SFML/Graphics.hpp>

class Button {
public:
    Button() = default;
    Button(const sf::Vector2f size);
    Button(const sf::Vector2f size, const sf::Vector2f position);
    Button(const sf::Vector2f size, const sf::Vector2f position, const std::function<void()>& func);
    Button(const sf::Vector2f size, const sf::Vector2f position, const sf::Texture* texture);
    Button(const sf::Vector2f size, const sf::Vector2f position, const sf::Texture* texture, const std::function<void()>& func);

    void setPosition(const sf::Vector2f);
    void setSize(const sf::Vector2f);
    void setText(const std::string& text, const sf::Font* font, const unsigned int size = 12, const float offsetAmount = 0.f);
    void setTexture(const sf::Texture* texture);
    void setFunction(const std::function<void()>& func);
    void setColor(const sf::Color& color);
    void setTextInsideButton(bool);
    void setTextColor(sf::Color color);

    bool poll();
    
    void draw(sf::RenderWindow& target) const;

    bool isHovering() const;

    const sf::RectangleShape& getShape() const;

private:

    sf::Vector2f calculateTextPosition() const;

    sf::RectangleShape m_shape;
    bool m_hovering = false;
    InputState* m_input = nullptr;
    std::function<void()> m_clickFunc;
    sf::Text m_text;
    float m_textOffsetAmount = 0.f;
    bool m_textIsInsideButton = false;

    const sf::Color m_tintColor = { 127, 127, 127 };
};
