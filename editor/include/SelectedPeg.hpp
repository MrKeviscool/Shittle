#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <Peg.hpp>

namespace std {
	template<typename T>
	struct hash;
};

class SelectedPeg {
public:
	SelectedPeg() = delete;
	SelectedPeg(Peg* peg);
	~SelectedPeg();
	operator Peg* ();
	operator Peg* () const;
	bool operator==(const SelectedPeg& other) const;
	bool operator==(const Peg* pegPtr) const;
	Peg* getPeg();
	Peg* getPeg() const;
	sf::Shape& getSelectShape();
	const sf::Shape& getSelectShape() const;
	sf::Vector2f getSelectSize() const;

private:
	Peg* peg;
	PegShape shapeType;
	char shapeData[sizeof(Bigger<sf::CircleShape, sf::RectangleShape>::type)];
	const float circSelectIncrease = 1.3f;
	const sf::Vector2f rectSelectIncrease{ 1.3f, 1.3f };
	void setSelectedPos(const Peg* target);
	sf::Vector2f getSelectedSize(const Peg* target) const;
	friend std::hash<SelectedPeg>;
};

namespace std {
	template<>
	struct hash<SelectedPeg> {
		size_t operator()(const SelectedPeg& selected) const {
			return reinterpret_cast<size_t>(selected.peg);
		}
	};
}