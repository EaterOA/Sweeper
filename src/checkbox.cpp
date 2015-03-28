#include "checkbox.hpp"
#include "gameResourceManager.hpp"
#include "gameConfig.hpp"
#include "util.hpp"

bool Checkbox::init(Sweeper* game, std::string name)
{
    GUIComponent::init(game, name);
    m_clicking = false;
    m_box.setTexture(&resource.getTexture("checkbox_unchecked"));
    m_box.setSize(sf::Vector2f(17, 17));
    m_info.setFont(resource.getFont("opensans"));
    m_info.setColor(sf::Color(0, 0, 0));
    m_info.setCharacterSize(15);
    m_info.setString(name);
    setSize(sf::Vector2f(m_box.getSize().x + m_info.getLocalBounds().width + 5,
            MAX(m_box.getSize().y, m_info.getCharacterSize() * 1.2f)));

    return true;
}

void Checkbox::setPosition(sf::Vector2f pos)
{
    GUIComponent::setPosition(pos);
    m_box.setPosition(pos);
    m_info.setPosition(pos.x + m_box.getSize().x + 5, pos.y);
}

void Checkbox::processPress(sf::Event &e)
{
    if (e.mouseButton.button != sf::Mouse::Left)
        return;

    sf::Vector2f pt(e.mouseButton.x, e.mouseButton.y);

    if (contains(pt))
        setCheck(!isChecked());
}

bool Checkbox::isChecked() const
{
    return (bool)config.getInt(m_setting);
}

void Checkbox::setCheck(bool check)
{
    config.setInt(m_setting, check);
    m_box.setTexture(&resource.getTexture(
        check ? "checkbox_checked" : "checkbox_unchecked"
    ));
}

void Checkbox::bindSetting(std::string setting)
{
    m_setting = setting;
}

void Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_box, states);
    target.draw(m_info, states);
}
