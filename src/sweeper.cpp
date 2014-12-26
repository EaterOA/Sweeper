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
    mAgent.reset();
    gAgent.setBoardSize(mAgent.getBoardSize());
    gAgent.setBoardMines(mAgent.getMinefield());
    gAgent.setBoardNumbers(mAgent.getNumfield());
}

void Sweeper::tick(std::vector<sf::Event> &e, const sf::Time &t, sf::Vector2f m)
{
    // process events
    for (unsigned i = 0; i < e.size(); i++) {
        if (e[i].type == sf::Event::MouseButtonPressed) {
            std::cout << "HI!\n";
        }
    }

    gAgent.updateState(mAgent.getBoard(), mAgent.getStatus(), mAgent.getElapsed());
}

void Sweeper::draw(sf::RenderWindow &w) const
{
    w.draw(gAgent);
}
