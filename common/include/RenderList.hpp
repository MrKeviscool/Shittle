#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <vector>
#include <memory>

class RenderList {
public:
	RenderList(sf::RenderTarget* target);
	void display() const;
	void draw(const sf::Drawable* drawable);
	void clearList();
	void setTarget(sf::RenderTarget* target);
private:
	std::vector<const sf::Drawable*> m_drawables;
	sf::RenderTarget* m_target = nullptr;
};