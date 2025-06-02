#pragma once

#include <unordered_set>

#include "Peg.hpp"
#include "InputState.hpp"
#include "SelectedPeg.hpp"

void deselectAll(std::unordered_set<SelectedPeg>& selectedPegs);
bool isSelected(const std::unordered_set<SelectedPeg>& selectedPegs, Peg* peg);
void togglePegSelect(const InputState& input, Peg* peg, std::unordered_set<SelectedPeg>& selectedPegs);
void moveSelected(const sf::Vector2f amountToMove, std::unordered_set<SelectedPeg>& selectedPegs);
void moveSelected(const sf::Vector2i amountToMove, std::unordered_set<SelectedPeg>& selectedPegs);
void rotateSelected(const int delta, std::unordered_set<SelectedPeg>& selectedPegs);
void resizeSelected(const int delta, std::unordered_set<SelectedPeg>& selectedPegs);
Peg* getSelectedOnMouse(const InputState& input, std::unordered_set<SelectedPeg>& selectedPegs);