#ifndef GUICOMPONENT_HPP
#define GUICOMPONENT_HPP

#include <SFML/Graphics.hpp>

class GUIComponent : public sf::Drawable, public sf::Transformable
{
public:
    virtual void setTransform(sf::Vector2i pos, sf::Vector2i size);
    virtual bool init() { return true; };
    virtual void processPress(sf::Event &e) {};
    virtual void processRelease(sf::Event &e) {};
    virtual bool inside(sf::Vector2i pt);
    virtual sf::IntRect getRect() const;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {};

    sf::IntRect m_rect;
};

#endif
