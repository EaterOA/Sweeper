#ifndef GUICOMPONENT_HPP
#define GUICOMPONENT_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Sweeper;

class GUIComponent : public sf::Drawable, public sf::Transformable
{
public:
    virtual bool init(Sweeper* game, std::string name = "");
    virtual void tick(const sf::Time &t) {};
    virtual void processPress(sf::Event &e) {};
    virtual void processRelease(sf::Event &e) {};
    virtual bool contains(sf::Vector2f pt);
    virtual void setPosition(sf::Vector2f pos);
    virtual void setSize(sf::Vector2f size);
    virtual sf::Vector2f getPosition() const;
    virtual sf::Vector2f getSize() const;
    virtual sf::FloatRect getRect() const;
    std::string getName() const;
    Sweeper* getGame() const;
    GUIComponent* findComponent(std::string name);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {};

    sf::FloatRect m_rect;
    std::string m_name;
    Sweeper* m_game;
};

#endif
