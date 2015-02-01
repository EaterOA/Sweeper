#include "guiComponent.hpp"

void GUIComponent::setTransform(sf::Vector2i pos, sf::Vector2i size)
{
    m_rect = sf::IntRect(pos, size);
}

bool GUIComponent::inside(sf::Vector2i pt)
{
    return m_rect.contains(pt);
}

sf::IntRect GUIComponent::getRect() const
{
    return m_rect;
}
