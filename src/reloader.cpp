#include "reloader.hpp"
#include "gameResourceManager.hpp"
#include "gameConfig.hpp"
#include "sweeperBoard.hpp"
#include "slider.hpp"
#include "app.hpp"
#include "util.hpp"
#include "sweeper.hpp"

bool Reloader::init(Sweeper* game, std::string name)
{
    GUIComponent::init(game, "Reloader");
    m_button.setTexture(&resource.getTexture("reload"));
    m_clicking = false;
    m_depressed = false;

    return true;
}

void Reloader::setPosition(sf::Vector2f pos)
{
    GUIComponent::setPosition(pos);
    m_button.setPosition(pos);
}

void Reloader::setSize(sf::Vector2f size)
{
    GUIComponent::setSize(size);
    m_button.setSize(size);
}

void Reloader::tick(const sf::Time &t)
{
    sf::Vector2f mpos = util::conv<float>(sf::Mouse::getPosition(window));
    m_depressed = m_clicking && contains(mpos);
}

void Reloader::processPress(sf::Event &e)
{
    if (e.mouseButton.button != sf::Mouse::Left)
        return;

    sf::Vector2f pt(e.mouseButton.x, e.mouseButton.y);
    m_clicking = contains(pt);
}

void Reloader::processRelease(sf::Event &e)
{
    if (e.mouseButton.button != sf::Mouse::Left)
        return;
    if (!m_clicking)
        return;

    m_clicking = false;

    sf::Vector2f pt(e.mouseButton.x, e.mouseButton.y);
    if (contains(pt)) {
        SweeperBoard* board = (SweeperBoard*)findComponent("SweeperBoard");
        int mine_perc = ((Slider*)findComponent("Mine frequency"))->getValue();
        int board_height = ((Slider*)findComponent("Rows"))->getValue();
        int board_width = ((Slider*)findComponent("Columns"))->getValue();
        config.setInt("mine_perc", mine_perc);
        config.setInt("board_height", board_height);
        config.setInt("board_width", board_width);
        config.save();
        board->reset();
        getGame()->adjustWindow();
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
