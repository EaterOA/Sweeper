/*
--------------------------------------------------------------------------------
GameLayer
- Adds layer-management functions specific to WarDance
- Defines WarDance-specific layer types
--------------------------------------------------------------------------------
*/

#ifndef SWEEPER_HPP
#define SWEEPER_HPP

#include "sweepermechanics.hpp"
#include "sweepergraphics.hpp"

class Sweeper
{
public:
    virtual bool init();
    virtual void tick(std::vector<sf::Event> &e, const sf::Time &t, sf::Vector2f m);
    virtual void draw(sf::RenderWindow &w) const;
private:
    SweeperMechanics mAgent;
    SweeperGraphics gAgent;
};

#endif
