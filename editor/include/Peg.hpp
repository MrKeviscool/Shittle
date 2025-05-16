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

enum class PegType{
    blue,
    orange,
    green,
    purple
};

class Peg{
public:
    Peg(const PegShape pegShape, const PegType = PegType::blue);
    PegShape getShape() const;
    PegType getType() const;
private:
    PegShape m_pegShape;
    PegType m_pegType;
    alignas(Bigger<sf::CircleShape, sf::RectangleShape>::type) 
        char m_shapeData[sizeof(Bigger<sf::CircleShape, sf::RectangleShape>::type)];
};