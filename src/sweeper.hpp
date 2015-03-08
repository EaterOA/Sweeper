#ifndef SWEEPER_HPP
#define SWEEPER_HPP

#include <vector>
#include "sweeperBoard.hpp"
#include "reloader.hpp"

class Sweeper : public sf::Drawable, public sf::Transformable
{
public:
    bool init();
    void tick(std::vector<sf::Event> &e, const sf::Time &t);
    std::vector<GUIComponent*> components();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void adjustWindow();

    sf::Vector2i m_wsize;
    sf::RectangleShape m_background;
    std::vector<GUIComponent*> m_comps;
    SweeperBoard m_board;
    Reloader m_reload;
};

#endif
