#include "sweeperBoard.hpp"
#include "app.hpp"
#include "gameConfig.hpp"
#include "util.hpp"

bool SweeperBoard::init(Sweeper* game, std::string name)
{
    GUIComponent::init(game, "SweeperBoard");
    if (!mAgent.init()) return false;
    if (!gAgent.init()) return false;
    reset();

    return true;
}

void SweeperBoard::reset()
{
    m_status = 0;
    mAgent.reset();
    gAgent.newBoard(mAgent.getSize(), mAgent.getMinefield(), mAgent.getNumfield());
    gAgent.updateBoard(mAgent.getBoard(), m_status, false, false, m_pressLoc);
    setSize(gAgent.calculateSizeInPixels());
}

void SweeperBoard::updateGraphics()
{
    sf::Vector2f m = util::conv<float>(sf::Mouse::getPosition(window)) - getPosition();
    sf::Vector2i mcur = gAgent.getTile(m.x, m.y);
    gAgent.updateBoard(
        mAgent.getBoard(),
        m_status,
        m_leftClicking && m_pressLoc == mcur,
        m_leftClicking && m_rightClicking,
        m_pressLoc
    );
}

void SweeperBoard::processPress(sf::Event &e)
{
    if (m_status != 0)
        return;

    sf::Vector2f mPos(e.mouseButton.x, e.mouseButton.y);
    sf::Vector2f mLocal = mPos - getPosition();
    sf::Vector2i loc = gAgent.getTile(mLocal.x, mLocal.y);

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
}

void SweeperBoard::processRelease(sf::Event &e)
{
    if (m_status != 0)
        return;

    sf::Vector2f mPos(e.mouseButton.x, e.mouseButton.y);
    sf::Vector2f mLocal = mPos - getPosition();
    sf::Vector2i loc = gAgent.getTile(mLocal.x, mLocal.y);

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
}

void SweeperBoard::tick(const sf::Time &t)
{
    updateGraphics();
}

void SweeperBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Transform t;
    sf::Vector2f pos = getPosition();
    t.translate(pos.x, pos.y);
    sf::RenderStates newState(t);
    target.draw(gAgent, newState);
}
