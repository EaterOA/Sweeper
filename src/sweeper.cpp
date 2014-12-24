#include "gameconfig.hpp"
#include "util.hpp"
#include "sweeper.hpp"
#include "sweepermechanics.hpp"
#include "sweepergraphics.hpp"
#include <iostream>

bool Sweeper::init()
{
    mAgent = new SweeperMechanics();
    gAgent = new SweeperGraphics();
    if (!mAgent->init()) return false;
    if (!gAgent->init()) return false;

    return true;
}

void Sweeper::tick(std::vector<sf::Event> &e, const sf::Time &t, sf::Vector2f m)
{
    // process events
    for (unsigned i = 0; i < e.size(); i++) {
        if (e[i].type == sf::Event::MouseButtonPressed) {
            std::cout << "HI!\n";
        }
    }
}

void Sweeper::draw(sf::RenderWindow &w) const
{
    w.draw(*gAgent);
}
