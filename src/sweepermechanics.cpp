#include "gameconfig.hpp"
#include "sweepermechanics.hpp"
#include "sweeperengine.hpp"

bool SweeperMechanics::init()
{
    m_board = NULL;
    m_engine = NULL;
    reset();
    return true;
}

void SweeperMechanics::reset()
{
    m_elapsed = 0;
}


void SweeperMechanics::start()
{
}

void SweeperMechanics::tick(const sf::Time &elapsed)
{
}

int** SweeperMechanics::getBoard()
{
    return m_board;
}

int SweeperMechanics::getStatus()
{
    return m_status;
}

sf::Vector2f SweeperMechanics::getBoardSize()
{
    return sf::Vector2f(m_engine->getX(), m_engine->getY());
}

double SweeperMechanics::getElapsed()
{
    return m_elapsed;
}
