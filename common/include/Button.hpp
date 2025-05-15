#include "InputState.hpp"

#include <SFML/Graphics.hpp>

#include <functional>

class Button{
public:
    Button() = default;
    Button(const sf::Vector2f size);
    Button(const sf::Vector2f size, const sf::Vector2f position);
    Button(const sf::Vector2f size, const sf::Vector2f position, std::function<void()> func);
    Button(const sf::Vector2f size, const sf::Vector2f position, std::string textureName);
    Button(const sf::Vector2f size, const sf::Vector2f position, std::string textureName, std::function<void()> func);

    void setPosition(const sf::Vector2f);
    void setSize(const sf::Vector2f);

    bool poll();

    inline bool isHovering() const;

    sf::RectangleShape& getShape();
    const sf::RectangleShape& getTintShape() const;

private:
    sf::RectangleShape m_shape;
    sf::RectangleShape m_tintShape;
    bool m_hovering = false;
    InputState* m_input = nullptr;
    std::function<void()> m_clickFunc;

    const sf::Color tintColor = {127, 127, 127, 127};
};