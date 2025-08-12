#include "Scaler.hpp"
#include <SFML/System/Vector2.hpp>

template <typename T>
struct ConstexprVec2 {
    T x,y;
    
    constexpr ConstexprVec2<T>() = default;
    constexpr ConstexprVec2<T>(const T x, const T y) : x(x), y(y){};
    constexpr ConstexprVec2<T>(const sf::Vector2<T> v) : x(v.x), y(v.y){};

    operator sf::Vector2<T>() const {
        return {x, y};
    }
};

using ConstexprVec2i = ConstexprVec2<int>;
using ConstexprVec2f = ConstexprVec2<float>;
using ConstexprVec2u = ConstexprVec2<unsigned int>;

constexpr static ConstexprVec2f getScaleFactor(const ConstexprVec2u base, const ConstexprVec2u current){
    return {
        base.x / static_cast<float>(current.x),
        base.y / static_cast<float>(current.y)
    };
}

Scaler::Scaler(const sf::Vector2u baseWindowSize, const sf::Vector2u currentWindowSize) : baseWindowSize(baseWindowSize){
    scaleFactor = getScaleFactor(baseWindowSize, currentWindowSize);
}

void Scaler::setNewWindowSize(const sf::Vector2u newWindowSize){
    scaleFactor = getScaleFactor(baseWindowSize, newWindowSize);
}

void Scaler::apply(sf::Transformable& transformable) const {
    transformable.setScale(scaleFactor);
}

sf::Vector2i Scaler::scalePixelPos(const sf::Vector2i pos) const {
    return {
        static_cast<const int>(pos.x * scaleFactor.x),
        static_cast<const int>(pos.y * scaleFactor.y)
    };
}
