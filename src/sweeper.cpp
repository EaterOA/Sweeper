#include "sweeper.hpp"
#include "app.hpp"
#include "gameConfig.hpp"
#include "util.hpp"

bool Sweeper::init()
{
    return true;
}

void Sweeper::processPress(sf::Event &e)
{
}

void Sweeper::processRelease(sf::Event &e)
{
}

void Sweeper::tick(std::vector<sf::Event> &e, const sf::Time &t)
{
    // process events
    for (int i = 0; i < (int)e.size(); i++) {
        if (e[i].type == sf::Event::MouseButtonPressed)
            processPress(e[i]);
        else if (e[i].type == sf::Event::MouseButtonReleased)
            processRelease(e[i]);
    }
}

void Sweeper::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}
