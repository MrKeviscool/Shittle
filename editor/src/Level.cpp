#include "Level.hpp"

Level::operator SerializedLevelWrite() {
	SerializedLevelWrite out({}, thumbnail.name, background, thumbnail.image);
	for (const auto& peg : pegs)
		out.pegs.emplace_back(peg);
	return out;
}