#pragma once

namespace sf {
	class RenderWindow;
};

namespace std {
	template<typename _Ty>
	class allocator;

	template <class _Elem>
	struct char_traits;

	template <class _Kty>
	struct hash;

	template <class _Ty>
	struct equal_to;

	template <typename _Elem, typename _Traits, typename _Alloc>
	class basic_string;

	template <typename _Ty1, typename _Ty2>
	struct pair;

	template <typename _Kty, typename _Ty, typename _Hasher, typename _Keyeq, typename _Alloc>
	class unordered_map;
};

class InputState;
class ResourceManager;
class Button;

void runEditor(sf::RenderWindow& window,
	InputState& input,
	ResourceManager& resources,
	std::unordered_map<std::basic_string<char, std::char_traits<char>, std::allocator<char>>, Button, std::hash<std::basic_string<char, std::char_traits<char>, std::allocator<char>>>, std::equal_to<std::basic_string<char, std::char_traits<char>, std::allocator<char>>>, std::allocator<std::pair<const std::basic_string<char, std::char_traits<char>, std::allocator<char>>, Button>>>& buttons
);