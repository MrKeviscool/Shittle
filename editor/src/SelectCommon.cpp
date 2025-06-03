#include "SelectCommon.hpp"

#include "PegCommon.hpp"
#include "SelectedPeg.hpp"

void deselectAll(std::unordered_set<SelectedPeg>& selectedPegs) {
	selectedPegs.clear();
}

bool isSelected(const std::unordered_set<SelectedPeg>& selectedPegs, Peg* peg) {
	return selectedPegs.find(peg) != selectedPegs.end();
}

void togglePegSelect(const InputState& input, Peg* peg, std::unordered_set<SelectedPeg>& selectedPegs) {
	if (!peg) return;

	if (selectedPegs.find(peg) == selectedPegs.end())
		selectedPegs.emplace(peg);
	else
		selectedPegs.erase(peg);
}

void moveSelected(const sf::Vector2f amountToMove, std::unordered_set<SelectedPeg>& selectedPegs){
	for(const SelectedPeg& selected : selectedPegs){
		selected.getPeg()->getShape().move(amountToMove);
		const_cast<SelectedPeg&>(selected).getSelectShape().move(amountToMove);
	}
}

void moveSelected(const sf::Vector2i amountToMove, std::unordered_set<SelectedPeg>& selectedPegs) {
	moveSelected(sf::Vector2f{static_cast<float>(amountToMove.x), static_cast<float>(amountToMove.y)}, selectedPegs);
}

void rotateSelected(const int delta, std::unordered_set<SelectedPeg>& selectedPegs){
	for(const SelectedPeg& _selectedPeg : selectedPegs){
		SelectedPeg& selectedPeg = const_cast<SelectedPeg&>(_selectedPeg);
		rotateInPlace(selectedPeg.getPeg(), delta);
		rotateInPlace(selectedPeg.getSelectShape(), _selectedPeg.getSelectSize(), delta);
	}
}

void resizeSelected(const int delta, std::unordered_set<SelectedPeg>& selectedPegs) {
	for (const SelectedPeg& cSelected : selectedPegs) {
		SelectedPeg& selected = const_cast<SelectedPeg&>(cSelected);
		resizeInPlace(selected.getPeg(), delta);
		resizeInPlace(selected.getSelectShape(), selected.getPeg()->getShapeType(), delta);
	}
}

Peg* getSelectedOnMouse(const InputState& input, std::unordered_set<SelectedPeg>& selectedPegs) {
	for (Peg* pegPtr : selectedPegs) {
		if (pegPtr->contains({static_cast<float>(input.mousePos().x), static_cast<float>(input.mousePos().y)}))
			return pegPtr;
	}
	return nullptr;
}