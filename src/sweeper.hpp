#ifndef SWEEPER_HPP
#define SWEEPER_HPP

#include <vector>
#include "guiComponent.hpp"

class Sweeper : public sf::Drawable, public sf::Transformable
{
public:
    bool init();
    void tick(std::vector<sf::Event> &e, const sf::Time &t);
    std::vector<GUIComponent*> components();
    void adjustWindow();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Vector2i m_wsize;
    std::vector<GUIComponent*> m_comps;
};

#endif
