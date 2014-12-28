#ifndef SWEEPER_HPP
#define SWEEPER_HPP

#include "sweepermechanics.hpp"
#include "sweepergraphics.hpp"

class Sweeper
{
public:
    bool init();
    void reset();
    void tick(std::vector<sf::Event> &e, const sf::Time &t, sf::Vector2f m);
    void draw(sf::RenderWindow &w) const;
private:
    SweeperMechanics mAgent;
    SweeperGraphics gAgent;
    int m_status;
    double m_elapsed;
};

#endif
