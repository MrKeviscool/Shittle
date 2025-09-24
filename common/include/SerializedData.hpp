#pragma once

#include <vector>
#include <functional>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Image.hpp>

#include "PegShape.hpp"

struct SerializedPeg {
	sf::Vector2f position;
	sf::Vector2f size;
	float rotation;
	PegShape shape;
};

struct SerializedLevelWrite {
	std::vector<SerializedPeg> pegs;
	const std::string& name;
	const sf::Image& background;
	const sf::Image& thumbnail;

	SerializedLevelWrite(
		const std::vector<SerializedPeg>& pegs,
		const std::string& name,
		const sf::Image& background,
		const sf::Image& thumbnail
	) : pegs(pegs), name(name), background(background), thumbnail(thumbnail) {}

};

struct SerializedThumbnailRead {
	std::string name;
	sf::Image thumbnail;
};

struct SerializedLevelRead {
	std::vector<SerializedPeg> pegs;
	sf::Image background;
};
