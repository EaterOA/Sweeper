#include "app.hpp"
#include "sweeper.hpp"
#include "guiComponent.hpp"

bool Sweeper::init()
{
    m_background.setFillColor(sf::Color(210, 210, 210));

    sf::Vector2i m_space(20, 20);

    m_board.init();
    m_board.setTransform(m_space, m_board.getSize());
    m_reload.init();
    m_reload.setTransform(sf::Vector2i(m_space.x * 2 + m_board.getSize().x,
                                       m_space.y),
                          sf::Vector2i(50, 50));

    m_comps.push_back(&m_board);
    m_comps.push_back(&m_reload);

    m_wsize.x = m_space.x * 3 + m_board.getRect().width + 50;
    m_wsize.y = m_space.y * 2 + m_board.getRect().height;
    adjustWindow();

    return true;
}

void Sweeper::adjustWindow()
{
    sf::Vector2u wsize(m_wsize.x, m_wsize.y);
    sf::View view(sf::FloatRect(0, 0, wsize.x, wsize.y));
    window.setView(view);
    window.setSize(wsize);

    m_background.setSize(sf::Vector2f(wsize.x, wsize.y));
}

void Sweeper::processPress(sf::Event &e)
{
    for (int i = 0; i < (int)m_comps.size(); i++)
        m_comps[i]->processPress(e);
}

void Sweeper::processRelease(sf::Event &e)
{
    for (int i = 0; i < (int)m_comps.size(); i++)
        m_comps[i]->processRelease(e);
}

void Sweeper::tick(std::vector<sf::Event> &e, const sf::Time &t)
{
    // process events
    for (int i = 0; i < (int)e.size(); i++) {
        if (e[i].type == sf::Event::MouseButtonPressed)
            processPress(e[i]);
        else if (e[i].type == sf::Event::MouseButtonReleased)
            processRelease(e[i]);
    }
}

void Sweeper::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_background);
    target.draw(m_board);
    target.draw(m_reload);
}
