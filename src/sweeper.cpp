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
            sf::Vector2<unsigned> tile = gAgent.getTile(e[i].mouseButton.x, e[i].mouseButton.y);
            if (tile.x == 1 && tile.y == 2)
                std::cout << "HI!\n";
        }
    }

    gAgent.updateState(mAgent.getBoard(), m_status, m_elapsed);
}

void Sweeper::draw(sf::RenderWindow &w) const
{
    w.draw(gAgent);
}
