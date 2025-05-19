#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

template <typename A, typename B, bool aBigger = (sizeof(A) > sizeof(B))>
struct Bigger{
    using type = B;
};

template <typename A, typename B>
struct Bigger<A, B, true>{
    using type = A;
};


enum class PegShape{
    Circle,
    Rect,
};

class Peg{
public:
    Peg(const PegShape pegShape);
    PegShape getShapeType() const;
    sf::Shape& getShape();
    bool contains(const sf::Vector2f pos) const;
    
private:
    PegShape m_pegShape;
    alignas(Bigger<sf::CircleShape, sf::RectangleShape>::type) 
        char m_shapeData[sizeof(Bigger<sf::CircleShape, sf::RectangleShape>::type)];
};