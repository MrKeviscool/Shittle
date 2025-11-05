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

	inline operator SerializedLevelWrite<decltype(pegs)::iterator>();
	Level(
		std::forward_list<Peg> pegs,
		sf::Image background,
		LevelThumbnail& thumbnail
	) : pegs(pegs),
		background(background),
		thumbnail(thumbnail){}
};

struct LevelPegGetter {
	static decltype(Level::pegs)& operator()(Level& lev) {
		return lev.pegs;
	}
};

Level::operator SerializedLevelWrite<decltype(Level::pegs)::iterator>() {
	return SerializedLevelWrite<decltype(pegs)::iterator>(pegs.begin(), pegs.end(), thumbnail.name, background, thumbnail.image);
}
