#include "InputState.hpp"

#include <SFML/Graphics.hpp>

class Button{
public:
    Button() = default;
    Button(sf::Vector2f position);
    Button(sf::Vector2f position, sf::Vector2f size);

    void poll();

    bool isHovering() const;

    sf::RectangleShape& getShape() const;
    sf::RectangleShape& getTintShape() const;

private:
    sf::RectangleShape m_shape;
    sf::RectangleShape m_tintShape;
    bool m_hovering;
    InputState* m_input = nullptr;
};