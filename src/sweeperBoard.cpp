#include "sweeperBoard.hpp"
#include "app.hpp"
#include "gameConfig.hpp"
#include "util.hpp"

bool SweeperBoard::init()
{
    if (!mAgent.init()) return false;
    if (!gAgent.init()) return false;
    reset();

    return true;
}

void SweeperBoard::setTransform(sf::Vector2i pos, sf::Vector2i size)
{
    gAgent.setOffset(pos);
    GUIComponent::setTransform(pos, size);
}

void SweeperBoard::reset()
{
    m_status = 0;
    mAgent.reset();
    gAgent.newBoard(mAgent.getSize(), mAgent.getMinefield(), mAgent.getNumfield());
    gAgent.updateBoard(mAgent.getBoard(), m_status, false, false, m_pressLoc);
}

void SweeperBoard::updateGraphics()
{
    sf::Vector2i m = sf::Mouse::getPosition(window);
    sf::Vector2i mcur = gAgent.getTile(m.x, m.y);
    bool pressingInitLoc = m_leftClicking && m_pressLoc == mcur;
    gAgent.updateBoard(mAgent.getBoard(), m_status, pressingInitLoc, m_leftClicking && m_rightClicking, m_pressLoc);
}

void SweeperBoard::processPress(sf::Event &e)
{
    sf::Vector2i loc = gAgent.getTile(e.mouseButton.x, e.mouseButton.y);

    if (loc.x == -1) {
        m_leftClicking = m_rightClicking = false;
        return;
    }

    if (e.mouseButton.button == sf::Mouse::Left) {
        m_leftClicking = true;
        if (m_rightClicking && m_pressLoc != loc)
            m_rightClicking = false;
    }
    else if (e.mouseButton.button == sf::Mouse::Right) {
        m_rightClicking = true;
        if (m_leftClicking && m_pressLoc != loc)
            m_leftClicking = false;
    }
    m_pressLoc = loc;

    updateGraphics();
}

void SweeperBoard::processRelease(sf::Event &e)
{
    if (m_status != 0)
        return;

    sf::Vector2i loc = gAgent.getTile(e.mouseButton.x, e.mouseButton.y);

    if (m_leftClicking || m_rightClicking) {
        if (m_pressLoc == loc) {
            if (m_leftClicking && m_rightClicking)
                m_status = mAgent.triggerTile(loc.y, loc.x);
            else if (m_leftClicking)
                m_status = mAgent.openTile(loc.y, loc.x);
            else if (m_rightClicking)
                m_status = mAgent.flagTile(loc.y, loc.x);
        }
    }
    m_leftClicking = m_rightClicking = false;

    if (m_status == 1)
        mAgent.markWrongTiles();

    updateGraphics();
}

void SweeperBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Transform t;
    sf::IntRect r = getRect();
    t.translate(r.left, r.top);
    sf::RenderStates newState(t);
    target.draw(gAgent, newState);
}

sf::Vector2i SweeperBoard::getSize()
{
    return gAgent.calculateSize();
}
