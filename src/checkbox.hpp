#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "guiComponent.hpp"

class Checkbox: public GUIComponent
{
public:
    virtual bool init(Sweeper* game, std::string name = "");
    virtual void processPress(sf::Event &e);
    virtual void processRelease(sf::Event &e);
    virtual void setPosition(sf::Vector2f pos);
    bool isChecked() const;
    void setCheck(bool check);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void updateInfo();
    void adjustComponents();

    bool m_check;
    sf::Text m_info;
    sf::RectangleShape m_box;
    bool m_clicking;
};

#endif
