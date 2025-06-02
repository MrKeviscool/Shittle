#pragma once

#include <forward_list>
#include <vector>

#include "Peg.hpp"
#include "InputState.hpp"

void resizeInPlace(Peg* peg, const int resizeSteps);
void resizeInPlace(sf::Shape& peg, const PegShape shape, const int resizeSteps);
void rotateInPlace(Peg* peg, const int rotationSteps);
void rotateInPlace(sf::Shape& peg, const sf::Vector2f size, const int rotationSteps);
Peg* getPegAtPosition(const sf::Vector2i pos, std::forward_list<Peg>& pegs);
Peg* getPegAtPosition(const sf::Vector2f pos, std::forward_list<Peg>&pegs);
Peg* getPegOnMouse(const InputState& input, std::forward_list<Peg>& pegs);
std::vector<Peg*> getPegsOnMouse(const InputState& input, std::forward_list<Peg>& pegs);