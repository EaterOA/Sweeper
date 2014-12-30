#include "sweeper.hpp"
#include "gameconfig.hpp"
#include "util.hpp"
#include <iostream>

bool Sweeper::init()
{
    if (!mAgent.init()) return false;
    if (!gAgent.init()) return false;
    reset();

    return true;
}

void Sweeper::reset()
{
    m_elapsed = 0;
    m_status = 0;
    mAgent.reset();
    gAgent.newBoard(mAgent.getSize(), mAgent.getMinefield(), mAgent.getNumfield());
}

void Sweeper::tick(std::vector<sf::Event> &e, const sf::Time &t, sf::Vector2f m)
{
    // track time
    if (m_status == 0)
        m_elapsed += t.asSeconds();

    // process events
    for (unsigned i = 0; i < e.size(); i++) {
        if (e[i].type == sf::Event::MouseButtonPressed) {
            m_pressing = true;
            m_pressLoc = gAgent.getTile(e[i].mouseButton.x, e[i].mouseButton.y);
            if (m_pressLoc.x == (unsigned)-1)
                m_pressing = false;
        }
        else if (e[i].type == sf::Event::MouseButtonReleased) {
            if (m_pressing) {
                sf::Vector2<unsigned> cur = gAgent.getTile(e[i].mouseButton.x, e[i].mouseButton.y);
                if (m_pressLoc.x == cur.x && m_pressLoc.y == cur.y)
                    m_status = mAgent.openTile(cur.y, cur.x);
                m_pressing = false;
            }
        }
        else if (e[i].type == sf::Event::MouseLeft) {
            m_pressing = false;
        }
    }
    sf::Vector2<unsigned> mcur = gAgent.getTile(m.x, m.y);
    bool pressingInitLoc = m_pressing && m_pressLoc.x == mcur.x && m_pressLoc.y == mcur.y;

    gAgent.updateBoard(mAgent.getBoard(), m_status, pressingInitLoc, false, m_pressLoc);
    gAgent.updateTimer(m_elapsed);
}

void Sweeper::draw(sf::RenderWindow &w) const
{
    w.draw(gAgent);
}
