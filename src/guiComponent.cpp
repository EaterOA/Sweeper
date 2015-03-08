#include "sweeper.hpp"
#include "guiComponent.hpp"

bool GUIComponent::init(Sweeper* game, std::string name)
{
    m_game = game;
    m_name = name;
    return true;
}

void GUIComponent::setSize(sf::Vector2f size)
{
    m_rect.width = size.x;
    m_rect.height = size.y;
}

void GUIComponent::setPosition(sf::Vector2f pos)
{
    m_rect.left = pos.x;
    m_rect.top = pos.y;
}

sf::Vector2f GUIComponent::getSize() const
{
    return sf::Vector2f(m_rect.width, m_rect.height);
}

sf::Vector2f GUIComponent::getPosition() const
{
    return sf::Vector2f(m_rect.left, m_rect.top);
}

bool GUIComponent::contains(sf::Vector2f pt)
{
    return m_rect.contains(pt);
}

sf::FloatRect GUIComponent::getRect() const
{
    return m_rect;
}

std::string GUIComponent::getName() const
{
    return m_name;
}

Sweeper* GUIComponent::getGame() const
{
    return m_game;
}

GUIComponent* GUIComponent::findComponent(std::string name)
{
    Sweeper* game = getGame();
    std::vector<GUIComponent*> c = game->components();
    for (int i = 0; i < (int)c.size(); i++) {
        if (c[i]->getName() == name) {
            return c[i];
        }
    }
    return NULL;
}
