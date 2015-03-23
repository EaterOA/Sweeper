#ifndef TIMER_HPP
#define TIMER_HPP

#include "guiComponent.hpp"

class Timer: public GUIComponent
{
public:
    virtual bool init(Sweeper* game, std::string name = "");
    virtual void tick(const sf::Time &t);
    virtual void setPosition(sf::Vector2f pos);
    int getElapsed() const;
    void start();
    void stop();
    void reset();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    double m_elapsed;
    bool m_counting;
    sf::Text m_info;
};

#endif
