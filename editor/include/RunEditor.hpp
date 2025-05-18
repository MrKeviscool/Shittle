#pragma once

namespace sf {
	class RenderWindow;
};

namespace std {
	template<typename _Ty>
	class allocator;

	template<typename _Ty, typename _Alloc>
	class vector;
};

class InputState;
class ResourceManager;
class Button;

void runEditor(sf::RenderWindow& window,
	InputState& input,
	ResourceManager& resources,
	std::vector<Button, std::allocator<Button>>& buttons);