#include "reloader.hpp"
#include "gameResourceManager.hpp"

bool Reloader::init()
{
    m_button.setTexture(&resource.getTexture("reload"));
    m_clicking = false;

    return true;
}

void Reloader::setTransform(sf::Vector2i pos, sf::Vector2i size)
{
    m_button.setPosition(sf::Vector2f(pos.x, pos.y));
    m_button.setSize(sf::Vector2f(size.x, size.y));
}

void Reloader::processPress(sf::Event &e)
{
    sf::Vector2f pt(e.mouseButton.x, e.mouseButton.y);
    m_clicking = m_button.getGlobalBounds().contains(pt);
}

void Reloader::processRelease(sf::Event &e)
{
    if (!m_clicking)
        return;
    m_clicking = false;

    sf::Vector2f pt(e.mouseButton.x, e.mouseButton.y);
    if (m_button.getGlobalBounds().contains(pt)) {
    }
}

void Reloader::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_button);
}
