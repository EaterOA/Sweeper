#include "slider.hpp"
#include "app.hpp"
#include "gameResourceManager.hpp"
#include "util.hpp"
#include "gameConfig.hpp"
#include <sstream>

bool Slider::init(Sweeper* game, std::string name)
{
    GUIComponent::init(game, name);
    m_ditch.setFillColor(sf::Color(66, 66, 66));
    m_switch.setFillColor(sf::Color(234, 234, 234));
    m_switch.setOutlineColor(sf::Color(20, 20, 20));
    m_switch.setOutlineThickness(1);
    m_info.setFont(resource.getFont("opensans"));
    m_info.setColor(sf::Color(0, 0, 0));
    m_info.setCharacterSize(15);

    return true;
}

void Slider::bindSetting(std::string setting)
{
    m_setting = setting;
}

void Slider::setPosition(sf::Vector2f pos)
{
    GUIComponent::setPosition(pos);
    adjustComponents();
}

void Slider::setSize(sf::Vector2f size)
{
    GUIComponent::setSize(size);
    adjustComponents();
}

int Slider::getValue() const
{
    return config.getInt(m_setting);
}

void Slider::setValue(int value)
{
    config.setInt(m_setting, value);
    updateInfo();
    adjustComponents();
}

void Slider::adjustComponents()
{
    int value = getValue();

    sf::Vector2f size = getSize(), pos = getPosition();
    m_info.setPosition(pos.x, pos.y);
    int ioffset = m_info.getLocalBounds().height + 10;
    pos.y += ioffset;
    size.y -= ioffset;
    m_ditch.setPosition(sf::Vector2f(pos.x, pos.y + 0.2f * size.y));
    m_ditch.setSize(sf::Vector2f(size.x, 0.6f * size.y));
    m_switch.setSize(sf::Vector2f(size.x * 0.05f, size.y));
    float progress = (value - m_min) / (float)(m_max - m_min);
    m_switch.setPosition(sf::Vector2f(pos.x + progress * 0.93f * size.x + 0.01f * size.x, pos.y));
}

void Slider::updateInfo()
{
    std::stringstream ss;
    ss << getName() << ": " << getValue();
    m_info.setString(ss.str());
}

void Slider::tick(const sf::Time &t)
{
    if (m_clicking) {
        float mx = sf::Mouse::getPosition(window).x;
        mx -= m_switch.getSize().x * 0.5f;
        mx -= m_ditch.getPosition().x;
        float progress = mx / (0.95f * m_ditch.getSize().x);
        int value = progress * (m_max - m_min + 0.5f) + m_min;
        value = util::bound(value, m_min, m_max);
        setValue(value);
    }
}

void Slider::processPress(sf::Event &e)
{
    if (e.mouseButton.button != sf::Mouse::Left)
        return;

    sf::Vector2f pt(e.mouseButton.x, e.mouseButton.y);
    m_clicking = m_switch.getGlobalBounds().contains(pt) ||
                 m_ditch.getGlobalBounds().contains(pt);
}

void Slider::processRelease(sf::Event &e)
{
    if (e.mouseButton.button != sf::Mouse::Left)
        return;

    m_clicking = false;
}

void Slider::setBounds(int minimum, int maximum)
{
    m_min = minimum;
    m_max = maximum;
    setValue(util::bound(getValue(), m_min, m_max));
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_clicking) {
        sf::Transform t;
        states.transform = t;
    }
    target.draw(m_ditch, states);
    target.draw(m_switch, states);
    target.draw(m_info, states);
}
