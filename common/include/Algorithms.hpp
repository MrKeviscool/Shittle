#pragma once

#include <vector>

#include <SFML/System/Vector2.hpp>

//time-comlexity: O(n log (log n))
std::vector<int> getPrimes(const int to);

//time-complexity: O(log(min(a, b)))
unsigned int getGcf(const unsigned int a, const unsigned int b);

const int getDistance(const sf::Vector2i a, const sf::Vector2i b);