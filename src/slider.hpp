#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "guiComponent.hpp"

class Slider: public GUIComponent
{
public:
    virtual bool init(Sweeper* game, std::string name = "");
    virtual void tick(const sf::Time &t);
    virtual void processPress(sf::Event &e);
    virtual void processRelease(sf::Event &e);
    virtual void setPosition(sf::Vector2f pos);
    virtual void setSize(sf::Vector2f size);
    void setBounds(int minimum, int maximum);
    int getValue() const;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void adjustValue();
    void adjustComponents(sf::Vector2f pos, sf::Vector2f size);
    void adjustSwitchPos(sf::Vector2f pos, sf::Vector2f size);

    int m_value;
    int m_min, m_max;
    sf::RectangleShape m_ditch;
    sf::RectangleShape m_switch;
    bool m_clicking;
};

#endif
