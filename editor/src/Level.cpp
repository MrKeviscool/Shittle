#include "Level.hpp"

Level::operator SerializedLevelWrite() {
	SerializedLevelWrite out({}, name, background, thumbnail);
	for (const auto& peg : pegs)
		out.pegs.emplace_back(peg);
	return out;
}