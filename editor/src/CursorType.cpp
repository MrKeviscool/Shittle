#include "CursorType.hpp"

CursorType::CursorType() : peg(PegShape::Circle) {

};

CursorType::CursorType(const Peg peg, const bool isCursor) : peg(peg), isCursor(isCursor) {

};