#pragma once

#include "InputState.hpp"

#include <SFML/Graphics.hpp>

#include <functional>

class Button{
public:
    Button() = default;
    Button(const sf::Vector2f size);
    Button(const sf::Vector2f size, const sf::Vector2f position);
    Button(const sf::Vector2f size, const sf::Vector2f position, std::function<void()> func);
    Button(const sf::Vector2f size, const sf::Vector2f position, const sf::Texture* texture);
    Button(const sf::Vector2f size, const sf::Vector2f position, const sf::Texture* texture, std::function<void()> func);

    void setPosition(const sf::Vector2f);
    void setSize(const sf::Vector2f);
    void setText(const std::string& text, const sf::Font* font, const unsigned int size = 12, const float offsetAmount = 2);
    void setTexture(const sf::Texture* texture);
    void setFunction(std::function<void()> func);

    bool poll();
    
    void draw(sf::RenderWindow& target) const;

    bool isHovering() const;

    const sf::RectangleShape& getShape() const;
    const sf::RectangleShape& getTintShape() const;

private:
    sf::RectangleShape m_shape;
    sf::RectangleShape m_tintShape;
    bool m_hovering = false;
    InputState* m_input = nullptr;
    std::function<void()> m_clickFunc;
    sf::Text m_text;

    const sf::Color tintColor = {127, 127, 127, 127};
};