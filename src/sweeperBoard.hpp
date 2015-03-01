#ifndef SWEEPERBOARD_HPP
#define SWEEPERBOARD_HPP

#include "guiComponent.hpp"
#include "sweeperMechanics.hpp"
#include "sweeperGraphics.hpp"

class SweeperBoard : public GUIComponent
{
public:
    virtual bool init(Sweeper* game, std::string name = "");
    virtual void setTransform(sf::Vector2i pos, sf::Vector2i size);
    virtual void processPress(sf::Event &e);
    virtual void processRelease(sf::Event &e);
    sf::Vector2i getSize();
    void reset();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void updateGraphics();

    SweeperMechanics mAgent;
    SweeperGraphics gAgent;
    int m_status;
    double m_elapsed;

    bool m_leftClicking;
    bool m_rightClicking;
    sf::Vector2i m_pressLoc;
};

#endif
