#include "timer.hpp"
#include "gameResourceManager.hpp"
#include <cstdio>

bool Timer::init(Sweeper* game, std::string name)
{
    GUIComponent::init(game, name);
    m_info.setFont(resource.getFont("opensans"));
    m_info.setColor(sf::Color(0, 0, 0));
    m_info.setCharacterSize(25);
    m_info.setString("00:00");
    setSize(sf::Vector2f(m_info.getLocalBounds().width,
                         m_info.getCharacterSize() * 1.2f)); // hack due to
                                                             // height not
                                                             // computed right

    m_elapsed = 0;
    m_counting = false;

    return true;
}

void Timer::setPosition(sf::Vector2f pos)
{
    GUIComponent::setPosition(pos);
    m_info.setPosition(pos.x, pos.y);
}

int Timer::getElapsed() const
{
    return (int)m_elapsed;
}

void Timer::start()
{
    m_counting = true;
}

void Timer::stop()
{
    m_counting = false;
}

void Timer::reset()
{
    m_elapsed = 0;
}

void Timer::tick(const sf::Time &t)
{
    if (m_counting) {
        int before = (int)m_elapsed;
        m_elapsed += t.asSeconds();
        if (before == (int)m_elapsed)
            return;
        int minutes = (int)m_elapsed / 60;
        int seconds = (int)m_elapsed % 60;
        if (minutes > 59)
            m_info.setString("59:59");
        else {
            char buf[10];
            sprintf(buf, "%02d:%02d", minutes, seconds);
            m_info.setString(std::string(buf));
        }
    }
}

void Timer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_info, states);
}
