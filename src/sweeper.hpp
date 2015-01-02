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
    void processPress(sf::Event &e);
    void processRelease(sf::Event &e);

    SweeperMechanics mAgent;
    SweeperGraphics gAgent;
    int m_status;
    double m_elapsed;

    bool m_leftClicking;
    bool m_rightClicking;
    sf::Vector2<int> m_pressLoc;
};

#endif
