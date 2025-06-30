#include "MulColor.hpp"

MulColor MulColor::operator*(const float f) const {
   return MulColor{
        static_cast<const unsigned char>(r * f),
        static_cast<const unsigned char>(g * f),
        static_cast<const unsigned char>(b * f),
        static_cast<const unsigned char>(a * f)}; 
}

MulColor& MulColor::operator*=(const float f){
    *this = *this * f;
    return *this;
}

MulColor::MulColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) : sf::Color(r, g, b, a) 
{

}

MulColor::MulColor() : sf::Color(){

}

