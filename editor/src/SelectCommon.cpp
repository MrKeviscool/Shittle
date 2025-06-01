#include "SelectCommon.hpp"

#include "PegCommon.hpp"

void deselectAll(std::unordered_set<Peg*>& selectedPegs) {
	selectedPegs.clear();
}

bool isSelected(const std::unordered_set<Peg*>& selectedPegs, Peg* peg) {
	return selectedPegs.find(peg) != selectedPegs.end();
}

void togglePegSelect(const InputState& input, Peg* peg, std::unordered_set<Peg*>& selectedPegs) {
	if (!peg) return;

	if (selectedPegs.find(peg) == selectedPegs.end())
		selectedPegs.emplace(peg);
	else
		selectedPegs.erase(peg);
}

void moveSelected(const sf::Vector2f amountToMove, std::unordered_set<Peg*>& selectedPegs){
	for(Peg* pegPtr : selectedPegs){
		pegPtr->getShape().move(amountToMove);
	}
}

void moveSelected(const sf::Vector2i amountToMove, std::unordered_set<Peg*>& selectedPegs) {
	moveSelected(sf::Vector2f{static_cast<float>(amountToMove.x), static_cast<float>(amountToMove.y)}, selectedPegs);
}

void rotateSelected(const int delta, std::unordered_set<Peg*>& selectedPegs){
	for(auto pegPtr : selectedPegs){
		rotateInPlace(pegPtr, delta);
	}
}

void resizeSelected(const int delta, std::unordered_set<Peg*>& selectedPegs) {
	for (auto pegPtr : selectedPegs) {
		resizeInPlace(pegPtr, delta);
	}
}

Peg* getSelectedOnMouse(const InputState& input, std::unordered_set<Peg*>& selectedPegs) {
	for (auto peg : selectedPegs) {
		if (peg->contains({ static_cast<float>(input.mousePos().x), static_cast<float>(input.mousePos().y) }))
			return peg;
	}
	return nullptr;
}