#ifndef RELOADER_HPP
#define RELOADER_HPP

#include "guiComponent.hpp"

class Reloader: public GUIComponent
{
public:
    virtual bool init();
    virtual void setTransform(sf::Vector2i pos, sf::Vector2i size);
    virtual void processPress(sf::Event &e);
    virtual void processRelease(sf::Event &e);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::RectangleShape m_button;
    bool m_clicking;
};

#endif
