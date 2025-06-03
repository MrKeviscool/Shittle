#include "Algorithms.hpp"

#include <cmath>

std::vector<int> getPrimes(const int to){
	std::vector<bool> sieve;
	sieve.resize(to - 2, true);
	
	for(int sieveIndex = 2; sieveIndex <= std::sqrt(static_cast<float>(to)); sieveIndex++){
		if(!sieve[sieveIndex-2]) continue;
		for(int factorIndex = sieveIndex; factorIndex * sieveIndex < to; factorIndex++)
			sieve[(factorIndex * sieveIndex)-2] = false;
	}
	
	std::vector<int> out;
	for(int i = 0; i < static_cast<int>(sieve.size()); i++)
		if(sieve[i]) out.push_back(i+2);
	
	return out;

}

unsigned int getGcf(const unsigned int a, const unsigned int b){
	unsigned int _a = a, _b = b;
	while(const int remainder = _a % _b){
		_a = _b;
		_b = remainder;
	}
	return _b;
}

int getDistance(const sf::Vector2i a, const sf::Vector2i b) {
	const sf::Vector2i distance {
		std::abs(a.x - b.x),
		std::abs(a.y - b.y)
	};

	return static_cast<int>(std::roundf(std::sqrt(static_cast<float>(distance.x * distance.x + distance.y * distance.y))));
};

float getDistance(const sf::Vector2f a, const sf::Vector2f b){
	const sf::Vector2f distance = {
		std::abs(a.x - b.x),
		std::abs(a.y - b.y)
	};
	return std::sqrt(distance.x * distance.x + distance.y * distance.y);
}

sf::Vector2f getPoint(const float angle, const float length){
	return {
		std::cos((angle - 90) * DEG_TO_RAD) * length,
		std::sin((angle - 90) * DEG_TO_RAD) * length,
	};
}

float getAngle(const float aX, const float aY, const float bX, const float bY){
	return (std::atan2(aX - bX, bY - aY) * RAD_TO_DEG) + 180.f;
}

float getAngle(const sf::Vector2f a, const sf::Vector2f b){
	return getAngle(a.x, a.y, b.x, b.y);
}

sf::Vector2f getPointFromOffsets(const sf::Vector2f origin, const float angle, const sf::Vector2f length) {
	const float middleOffsetAngle = getAngle({ 0.f,0.f }, length);
	const float middleDistance = getDistance({ 0.f,0.f }, length);
	return getPoint(angle + middleOffsetAngle, middleDistance) + origin;
}