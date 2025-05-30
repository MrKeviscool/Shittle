#pragma once

#include <vector>

#include <SFML/System/Vector2.hpp>

#ifndef M_PIf
#define M_PIf 3.14159265358979323846f;
#endif

#define DEG_TO_RAD M_PIf / 180.f
#define RAD_TO_DEG 180.f / M_PIf

//time-comlexity: O(n log (log n))
std::vector<int> getPrimes(const int to);

//time-complexity: O(log(min(a, b)))
unsigned int getGcf(const unsigned int a, const unsigned int b);

int getDistance(const sf::Vector2i a, const sf::Vector2i b);
float getDistance(const sf::Vector2f a, const sf::Vector2f b);

sf::Vector2f getPoint(const float angle, const float distance);
float getAngle(const sf::Vector2f a, const sf::Vector2f b);
float getAngle(const float aX, const float aY, const float bX, const float bY);