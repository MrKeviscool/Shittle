#pragma once

#include <unordered_set>

#include "Peg.hpp"
#include "InputState.hpp"

void deselectAll(std::unordered_set<Peg*>& selectedPegs);
bool isSelected(const std::unordered_set<Peg*>& selectedPegs, Peg* peg);
void togglePegSelect(const InputState& input, Peg* peg, std::unordered_set<Peg*>& selectedPegs);
void moveSelected(const sf::Vector2f amountToMove, std::unordered_set<Peg*>& selectedPegs);
void moveSelected(const sf::Vector2i amountToMove, std::unordered_set<Peg*>& selectedPegs);
void rotateSelected(const int delta, std::unordered_set<Peg*>& selectedPegs);
void resizeSelected(const int delta, std::unordered_set<Peg*>& selectedPegs);
Peg* getSelectedOnMouse(const InputState& input, std::unordered_set<Peg*>& selectedPegs);