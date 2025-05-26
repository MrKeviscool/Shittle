#pragma once

#include <string>
#include <unordered_map>

#include "ButtonType.hpp"

namespace sf {
	class RenderWindow;
};

class InputState;
class ResourceManager;
class Button;

void runEditor(sf::RenderWindow& window,
	InputState& input,
	ResourceManager& resources,
	std::unordered_map<ButtonType, Button>& buttons
);