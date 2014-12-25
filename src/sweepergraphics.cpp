#include "util.hpp"
#include "gameconfig.hpp"
#include "sweepergraphics.hpp"

bool SweeperGraphics::init()
{
    if (!m_tilesheet.loadFromFile("img/tilesheet.png") ||
        !m_numbersheet.loadFromFile("img/numbersheet.png"))
        return false;

    m_background.setSize(sf::Vector2f(800, 600));
    m_background.setFillColor(sf::Color(210, 210, 210));

    return true;
}

void SweeperGraphics::updateState(int** board, int status, double elapsed)
{
}

void SweeperGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_background);
}

void SweeperGraphics::setBoardSize(sf::Vector2f boardSize)
{
    m_boardSize = boardSize;
}

void SweeperGraphics::setBoardNumbers(int** boardNumbers)
{
}
