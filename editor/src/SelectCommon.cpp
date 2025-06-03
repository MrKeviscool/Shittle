#include "SelectCommon.hpp"

#include <cmath>

#include "PegCommon.hpp"
#include "SelectedPeg.hpp"

const float rotationStepSize = 5.f;
const float scalePercent = 1.1f;

void deselectAll(std::unordered_set<SelectedPeg>& selectedPegs) {
	selectedPegs.clear();
}

bool isSelected(const std::unordered_set<SelectedPeg>& selectedPegs, Peg* peg) {
	return selectedPegs.find(peg) != selectedPegs.end();
}

void togglePegSelect(Peg* peg, std::unordered_set<SelectedPeg>& selectedPegs) {
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
	const float scaledRotationAmount = rotationStepSize * static_cast<float>(delta);
	for(const SelectedPeg& _selectedPeg : selectedPegs){
		SelectedPeg& selectedPeg = const_cast<SelectedPeg&>(_selectedPeg);
		rotateInPlace(selectedPeg.getPeg(), scaledRotationAmount);
		rotateInPlace(selectedPeg.getSelectShape(), _selectedPeg.getSelectSize(), scaledRotationAmount);
	}
}

void resizeSelected(const int delta, std::unordered_set<SelectedPeg>& selectedPegs) {
	const float deltadScalePercent = std::pow(scalePercent, static_cast<float>(delta));
	for (const SelectedPeg& cSelected : selectedPegs) {
		SelectedPeg& selected = const_cast<SelectedPeg&>(cSelected);
		scaleInPlace(selected.getPeg(), deltadScalePercent);
		scaleInPlace(selected.getSelectShape(), selected.getPeg()->getShapeType(), deltadScalePercent);
	}
}

Peg* getSelectedOnMouse(const InputState& input, std::unordered_set<SelectedPeg>& selectedPegs) {
	for (Peg* pegPtr : selectedPegs) {
		if (pegPtr->contains({static_cast<float>(input.mousePos().x), static_cast<float>(input.mousePos().y)}))
			return pegPtr;
	}
	return nullptr;
}