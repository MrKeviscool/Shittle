#pragma once

#include <vector>
#include <string>

#include "Peg.hpp"

struct Level {
public:
	std::vector<Peg> pegs;
	std::string name;
	sf::Image background;
	sf::Image thumbnail;
	operator SerializedLevelWrite();
};
