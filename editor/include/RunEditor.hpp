#pragma once

#include <string>
#include <unordered_map>

namespace sf {
	class RenderWindow;
};

class InputState;
class ResourceManager;
class Button;

void runEditor(sf::RenderWindow& window,
	InputState& input,
	ResourceManager& resources,
	std::unordered_map<std::string, Button>& buttons
);