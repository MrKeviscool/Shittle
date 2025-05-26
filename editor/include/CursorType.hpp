#pragma once

#include "Peg.hpp"

struct CursorType {
	Peg peg;
	bool isCursor = true;
	CursorType();
	CursorType(const Peg peg, const bool isCursor);
	CursorType& operator=(CursorType&& other) = default;
};