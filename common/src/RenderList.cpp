#include "RenderList.hpp"

RenderList::RenderList(sf::RenderTarget* target) : m_target(target) 
{

}

void RenderList::display() const {
	if (!m_target) return;
	for (auto drawPtr : m_drawables)
		m_target->draw(*drawPtr);
}

void RenderList::clearList() {
	m_drawables.clear();
}

void RenderList::setTarget(sf::RenderTarget* target) {
	m_target = target;
}

void RenderList::draw(const sf::Drawable* drawable) {
	m_drawables.push_back(drawable);
}