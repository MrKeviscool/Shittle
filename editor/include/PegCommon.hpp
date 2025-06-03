#pragma once

#include <forward_list>
#include <vector>

#include "Peg.hpp"
#include "InputState.hpp"

void scaleInPlace(Peg* peg, const float scalePercent);
void scaleInPlace(sf::Shape& peg, const PegShape shape, const float scalePercent);
void rotateInPlace(Peg* peg, const float rotation);
void rotateInPlace(sf::Shape& peg, const sf::Vector2f size, const float rotation);
Peg* getPegAtPosition(const sf::Vector2i pos, std::forward_list<Peg>& pegs);
Peg* getPegAtPosition(const sf::Vector2f pos, std::forward_list<Peg>&pegs);
Peg* getPegOnMouse(const InputState& input, std::forward_list<Peg>& pegs);
std::vector<Peg*> getPegsOnMouse(const InputState& input, std::forward_list<Peg>& pegs);