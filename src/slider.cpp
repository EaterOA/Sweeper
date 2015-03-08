#include "slider.hpp"

bool Slider::init(Sweeper* game, std::string name)
{
    GUIComponent::init(game, name);
    m_ditch.setFillColor(sf::Color(66, 66, 66));
    m_switch.setFillColor(sf::Color(214, 214, 214));

    return true;
}

void Slider::setPosition(sf::Vector2f pos)
{
    GUIComponent::setPosition(pos);
    adjustComponents(pos, getSize());
}

void Slider::setSize(sf::Vector2f size)
{
    GUIComponent::setSize(size);
    adjustComponents(getPosition(), size);
}

void Slider::adjustComponents(sf::Vector2f pos, sf::Vector2f size)
{
    m_ditch.setSize(sf::Vector2f(size.x, 0.6f * size.y));
    m_ditch.setPosition(sf::Vector2f(pos.x, pos.y + 0.2f * size.y));
    m_switch.setSize(sf::Vector2f(size.x * 0.05f, size.y));
    float progress = (m_value - m_min) / (float)(m_max - m_min);
    m_switch.setPosition(sf::Vector2f(pos.x + progress * 0.93f * size.x + 0.01f * size.x, pos.y));
}

void Slider::tick(const sf::Time &t)
{
}

void Slider::processPress(sf::Event &e)
{
    if (e.mouseButton.button != sf::Mouse::Left)
        return;

    sf::Vector2f pt(e.mouseButton.x, e.mouseButton.y);
    m_clicking = m_switch.getGlobalBounds().contains(pt);
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
    if (m_value < m_min)
        m_value = m_min;
    if (m_value > m_max)
        m_value = m_max;
    adjustComponents(getPosition(), getSize());
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_clicking) {
        sf::Transform t;
        states.transform = t;
    }
    target.draw(m_ditch, states);
    target.draw(m_switch, states);
}
