#include "guiComponent.hpp"

GUIComponent::GUIComponent(sf::Vector2i pos, sf::Vector2i size)
{
    m_rect = sf::IntRect(pos, size);
}

GUIComponent::GUIComponent(sf::IntRect rect)
{
    m_rect = rect;
}

bool GUIComponent::inside(sf::Vector2i pt)
{
    return m_rect.contains(pt);
}

sf::IntRect GUIComponent::getRect()
{
    return m_rect;
}
