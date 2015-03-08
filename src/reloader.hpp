#ifndef RELOADER_HPP
#define RELOADER_HPP

#include "guiComponent.hpp"

class Reloader: public GUIComponent
{
public:
    virtual bool init(Sweeper* game, std::string name = "");
    virtual void tick(const sf::Time &t);
    virtual void processPress(sf::Event &e);
    virtual void processRelease(sf::Event &e);
    virtual void setPosition(sf::Vector2f pos);
    virtual void setSize(sf::Vector2f size);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::RectangleShape m_button;
    bool m_clicking;
    bool m_depressed;
};

#endif
