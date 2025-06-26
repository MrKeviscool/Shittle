#include "MulColor.hpp"

MulColor MulColor::operator*(const float f){
   return MulColor{
        static_cast<unsigned char>(r * f),
        static_cast<unsigned char>(g * f),
        static_cast<unsigned char>(b * f),
        static_cast<unsigned char>(a * f)}; 
}

MulColor& MulColor::operator*=(const float f){
    *this = *this * f;
    return *this;
}

MulColor::MulColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : sf::Color(r, g, b, a) 
{

}

MulColor::MulColor() : sf::Color(){

}

