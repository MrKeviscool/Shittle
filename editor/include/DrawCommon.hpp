#pragma once

#include <unordered_map>
#include <forward_list>

#include "SFML/Graphics/RenderWindow.hpp"

#include "InputState.hpp"
#include "Button.hpp"
#include "ButtonType.hpp"
#include "CursorType.hpp"
#include "SelectedPeg.hpp"

void drawButtons(sf::RenderWindow& target, const std::unordered_map<ButtonType, Button>& buttons);
void drawCursorType(sf::RenderWindow& window, bool isButtonHovered, sf::Vector2i mousePos, CursorType& cursorType);
void drawPegs(sf::RenderWindow& window, const std::forward_list<Peg>& pegs);
void drawSelected(sf::RenderWindow& window, const std::unordered_set<SelectedPeg>& selectedPegs);