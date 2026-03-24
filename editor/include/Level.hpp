#pragma once

#include <string>
#include <forward_list>

#include "SerializedData.hpp"
#include "Peg.hpp"
#include "SFML/Graphics/Image.hpp"

struct LevelThumbnail {
	std::string name;
	sf::Image* image;
};

struct Level {
public:
	std::forward_list<Peg> pegs;
	sf::Image background;
	LevelThumbnail thumbnail;

	using PegIterator_t = decltype(pegs)::iterator;

	inline operator SerializedLevelWrite<Level::PegIterator_t>() {
		return SerializedLevelWrite<PegIterator_t> {
			pegs.begin(),
			pegs.end(),
			thumbnail.name,
			background,
			*thumbnail.image
		};
	}
};
