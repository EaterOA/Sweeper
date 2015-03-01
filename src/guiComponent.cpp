#include "sweeper.hpp"
#include "guiComponent.hpp"

bool GUIComponent::init(Sweeper* game, std::string name)
{
    m_game = game;
    m_name = name;
    return true;
}

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
