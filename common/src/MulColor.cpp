#include "MulColor.hpp"
#include <SFML/Graphics/Color.hpp>

MulColor MulColor::operator*(const float f) const {
   return MulColor{
		static_cast<const unsigned char>(r * f),
		static_cast<const unsigned char>(g * f),
		static_cast<const unsigned char>(b * f),
		static_cast<const unsigned char>(a * f)
   }; 
}

MulColor& MulColor::operator*=(const float f){
	*this = *this * f;
	return *this;
}

MulColor::MulColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) : sf::Color(r, g, b, a) 
{

}

MulColor::MulColor(const sf::Color& color){
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
}

MulColor::MulColor(const sf::Color& color, const float mul){
	r = static_cast<unsigned char>(color.r * mul);
	g = static_cast<unsigned char>(color.g * mul);
	b = static_cast<unsigned char>(color.b * mul);
}

MulColor::MulColor() : sf::Color(){

}

MulColor& MulColor::operator=(const sf::Color& col){
	this->r = col.r;
	this->g = col.g;
	this->b = col.b;
	this->a = col.a;
	return *this;
}
