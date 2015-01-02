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

void Sweeper::processPress(sf::Event &e)
{
    sf::Vector2<int> loc = gAgent.getTile(e.mouseButton.x, e.mouseButton.y);

    if (loc.x == -1) {
        m_leftClicking = m_rightClicking = false;
        return;
    }

    if (e.mouseButton.button == sf::Mouse::Left) {
        m_leftClicking = true;
        if (m_rightClicking && (m_pressLoc.x != loc.x || m_pressLoc.y != loc.y))
            m_rightClicking = false;
    }
    else if (e.mouseButton.button == sf::Mouse::Right) {
        m_rightClicking = true;
        if (m_leftClicking && (m_pressLoc.x != loc.x || m_pressLoc.y != loc.y))
            m_leftClicking = false;
    }
    m_pressLoc = loc;
}

void Sweeper::processRelease(sf::Event &e)
{
    sf::Vector2<int> loc = gAgent.getTile(e.mouseButton.x, e.mouseButton.y);

    if (m_leftClicking || m_rightClicking) {
        if (m_pressLoc.x == loc.x && m_pressLoc.y == loc.y) {
            if (m_leftClicking && m_rightClicking)
                m_status = mAgent.triggerTile(loc.y, loc.x);
            else if (m_leftClicking)
                m_status = mAgent.openTile(loc.y, loc.x);
            else if (m_rightClicking)
                m_status = mAgent.flagTile(loc.y, loc.x);
        }
    }
    m_leftClicking = m_rightClicking = false;
}

void Sweeper::tick(std::vector<sf::Event> &e, const sf::Time &t, sf::Vector2f m)
{
    if (m_status != 0)
        return;

    // track time
    if (m_status == 0)
        m_elapsed += t.asSeconds();

    // process events
    for (int i = 0; i < (int)e.size(); i++) {
        if (e[i].type == sf::Event::MouseButtonPressed)
            processPress(e[i]);
        else if (e[i].type == sf::Event::MouseButtonReleased)
            processRelease(e[i]);
        else if (e[i].type == sf::Event::MouseLeft)
            m_leftClicking = m_rightClicking = false;
    }
    sf::Vector2<int> mcur = gAgent.getTile(m.x, m.y);
    bool pressingInitLoc = m_leftClicking && m_pressLoc.x == mcur.x && m_pressLoc.y == mcur.y;

    gAgent.updateBoard(mAgent.getBoard(), m_status, pressingInitLoc, m_leftClicking && m_rightClicking, m_pressLoc);
    gAgent.updateTimer(m_elapsed);
}

void Sweeper::draw(sf::RenderWindow &w) const
{
    w.draw(gAgent);
}
