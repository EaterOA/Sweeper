#ifndef SWEEPER_HPP
#define SWEEPER_HPP

#include <vector>
#include "guiComponent.hpp"
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

    std::vector<GUIComponent> m_comps;
    SweeperBoard* m_board;
};

#endif
