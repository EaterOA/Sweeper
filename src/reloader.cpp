#include "reloader.hpp"
#include "gameResourceManager.hpp"
#include "sweeperBoard.hpp"
#include "app.hpp"

bool Reloader::init(Sweeper* game, std::string name)
{
    GUIComponent::init(game, "Reloader");
    m_button.setTexture(&resource.getTexture("reload"));
    m_clicking = false;
    m_depressed = false;

    return true;
}

void Reloader::setTransform(sf::Vector2i pos, sf::Vector2i size)
{
    m_button.setPosition(sf::Vector2f(pos.x, pos.y));
    m_button.setSize(sf::Vector2f(size.x, size.y));
}

void Reloader::tick(const sf::Time &t)
{
    sf::Vector2i mpos = sf::Mouse::getPosition(window);
    sf::Vector2f mposf(mpos.x, mpos.y);
    m_depressed = m_clicking && m_button.getGlobalBounds().contains(mposf);
}

void Reloader::processPress(sf::Event &e)
{
    if (e.mouseButton.button != sf::Mouse::Left)
        return;

    sf::Vector2f pt(e.mouseButton.x, e.mouseButton.y);
    m_clicking = m_button.getGlobalBounds().contains(pt);
}

void Reloader::processRelease(sf::Event &e)
{
    if (e.mouseButton.button != sf::Mouse::Left)
        return;
    if (!m_clicking)
        return;

    m_clicking = false;

    sf::Vector2f pt(e.mouseButton.x, e.mouseButton.y);
    if (m_button.getGlobalBounds().contains(pt)) {
        SweeperBoard* board = (SweeperBoard*)findComponent("SweeperBoard");
        board->reset();
    }
}

void Reloader::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_depressed) {
        sf::Transform t;
        sf::Vector2f pos = m_button.getPosition();
        sf::Vector2f size = m_button.getSize();
        t.scale(0.8, 0.8, pos.x + size.x/2, pos.y + size.y/2);
        states.transform = t;
    }
    target.draw(m_button, states);
}
