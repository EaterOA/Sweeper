#ifndef GUICOMPONENT_HPP
#define GUICOMPONENT_HPP

#include <SFML/Graphics.hpp>

class GUIComponent : public sf::Drawable, public sf::Transformable
{
public:
    GUIComponent() {};
    GUIComponent(sf::Vector2i pos, sf::Vector2i size);
    GUIComponent(sf::IntRect rect);
    virtual void init() {};
    virtual void processPress(sf::Event &e) {};
    virtual void processRelease(sf::Event &e) {};
    virtual bool inside(sf::Vector2i pt);
    virtual sf::IntRect getRect();
private:
    sf::IntRect m_rect;
};

#endif
