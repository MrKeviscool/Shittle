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
	int _a = a, _b = b;
	while(const int remainder = _a % _b){
		_a = _b;
		_b = remainder;
	}
	return _b;
}

const int getDistance(const sf::Vector2i a, const sf::Vector2i b) {
	const sf::Vector2i distance {
		std::abs(a.x - b.x),
		std::abs(a.y - b.y)
	};

	return static_cast<int>(std::roundf(std::sqrt(static_cast<float>(distance.x * distance.x + distance.y * distance.y))));

};