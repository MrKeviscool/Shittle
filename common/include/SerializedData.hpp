#pragma once

#include <vector>
#include <functional>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Image.hpp>

#include "PegShape.hpp"

struct SerializedPeg {
	sf::Vector2f position;
	sf::Vector2f size;
	float rotation = 0;
	PegShape shape = PegShape::Circle;
};

template <typename PegIter>//,
	//typename std::enable_if<
	//	std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<PegIter>::iterator_category>::value,
	//	//&& std::is_convertible<typename std::iterator_traits<PegIter>::value_type, SerializedPeg>::value,
	//int>::type = 0>
struct SerializedLevelWrite {
	PegIter pegsBeginIter, pegsEndIter;
	const std::string& name;
	const sf::Image& background;
	const sf::Image& thumbnail;

	SerializedLevelWrite(
		PegIter pegsBeginIter, PegIter pegsEndIter,
		const std::string& name,
		const sf::Image& background,
		const sf::Image& thumbnail
	) : pegsBeginIter(pegsBeginIter), pegsEndIter(pegsEndIter), name(name), background(background), thumbnail(thumbnail) { }

};

struct SerializedThumbnailRead {
	std::string name;
	sf::Image thumbnail;
};

struct SerializedLevelRead {
	std::vector<SerializedPeg> pegs;
	sf::Image background;
};
