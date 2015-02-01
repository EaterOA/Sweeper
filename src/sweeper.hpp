#ifndef SWEEPER_HPP
#define SWEEPER_HPP

#include <vector>
#include "sweeperBoard.hpp"

class Sweeper : public sf::Drawable, public sf::Transformable
{
public:
    bool init();
    void tick(std::vector<sf::Event> &e, const sf::Time &t);
    void draw() const;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void processPress(sf::Event &e);
    void processRelease(sf::Event &e);
    void adjustWindow();

    sf::Vector2i m_wsize;
    sf::RectangleShape m_background;
    std::vector<GUIComponent*> m_comps;
    SweeperBoard m_board;
};

#endif
