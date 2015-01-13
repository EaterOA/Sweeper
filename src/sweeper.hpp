#ifndef SWEEPER_HPP
#define SWEEPER_HPP

#include "sweeperMechanics.hpp"
#include "sweeperGraphics.hpp"

class Sweeper
{
public:
    bool init();
    void reset();
    void tick(std::vector<sf::Event> &e, const sf::Time &t);
    void draw() const;
private:
    void processPress(sf::Event &e);
    void processRelease(sf::Event &e);

    SweeperMechanics mAgent;
    SweeperGraphics gAgent;
    int m_status;
    double m_elapsed;

    bool m_leftClicking;
    bool m_rightClicking;
    sf::Vector2i m_pressLoc;
};

#endif
