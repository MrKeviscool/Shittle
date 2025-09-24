#pragma once

#include <string>
#include <forward_list>

#include "Peg.hpp"
#include "SFML/Graphics/Image.hpp"

struct LevelThumbnail {
	std::string name;
	sf::Image image;
};

struct Level {
public:
	std::forward_list<Peg> pegs;
	sf::Image background;
	LevelThumbnail& thumbnail;
	operator SerializedLevelWrite();
	Level(
		std::forward_list<Peg> pegs,
		sf::Image background,
		LevelThumbnail& thumbnail) : pegs(pegs),
		background(background),
		thumbnail(thumbnail){}
};

