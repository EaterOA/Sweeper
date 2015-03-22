#include "app.hpp"
#include "sweeper.hpp"
#include "util.hpp"
#include "sweeperBoard.hpp"
#include "reloader.hpp"
#include "slider.hpp"

bool Sweeper::init()
{
    sf::Vector2f m_space(20, 20);

    // Board
    SweeperBoard* board = new SweeperBoard();
    board->init(this);
    board->setPosition(m_space);
    // Reload button
    Reloader* reload = new Reloader();
    reload->init(this);
    reload->setPosition(sf::Vector2f(m_space.x * 2 + board->getSize().x, m_space.y));
    reload->setSize(sf::Vector2f(50, 50));
    // Mine frequency slider
    Slider* mf = new Slider();
    mf->init(this, "Mine frequency");
    mf->setBounds(20, 90);
    mf->setPosition(sf::Vector2f(m_space.x * 2 + board->getSize().x, m_space.y * 2 + reload->getSize().y));
    mf->setSize(sf::Vector2f(140, 40));
    // Rows slider
    Slider* r = new Slider();
    r->init(this, "Rows");
    r->setBounds(8, 30);
    r->setPosition(sf::Vector2f(m_space.x * 2 + board->getSize().x, m_space.y * 3 + reload->getSize().y + mf->getSize().y));
    r->setSize(sf::Vector2f(100, 40));
    // Columns slider
    Slider* c = new Slider();
    c->init(this, "Columns");
    c->setBounds(8, 30);
    c->setPosition(sf::Vector2f(m_space.x * 2 + board->getSize().x, m_space.y * 3.2 + reload->getSize().y + +mf->getSize().y + r->getSize().y));
    c->setSize(sf::Vector2f(100, 40));

    m_comps.push_back(board);
    m_comps.push_back(reload);
    m_comps.push_back(mf);
    m_comps.push_back(r);
    m_comps.push_back(c);

    m_wsize.x = m_space.x * 3 + board->getSize().x + mf->getSize().x;
    m_wsize.y = m_space.y * 2 + board->getSize().y;
    adjustWindow();

    return true;
}

void Sweeper::adjustWindow()
{
    sf::Vector2u wsize = util::conv<unsigned>(m_wsize);
    sf::View view(sf::FloatRect(0, 0, wsize.x, wsize.y));
    window.setView(view);
    window.setSize(wsize);
}

void Sweeper::tick(std::vector<sf::Event> &e, const sf::Time &t)
{
    // process events
    for (int n = 0; n < (int)e.size(); n++) {
        sf::Event& ev = e[n];

        // process press
        if (ev.type == sf::Event::MouseButtonPressed)
            for (int i = 0; i < (int)m_comps.size(); i++)
                m_comps[i]->processPress(ev);

        // process release
        else if (ev.type == sf::Event::MouseButtonReleased)
            for (int i = 0; i < (int)m_comps.size(); i++)
                m_comps[i]->processRelease(ev);
    }

    // tick components
    for (int i = 0; i < (int)m_comps.size(); i++)
        m_comps[i]->tick(t);
}

void Sweeper::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int i = 0; i < (int)m_comps.size(); i++)
        target.draw(*m_comps[i]);
}

std::vector<GUIComponent*> Sweeper::components()
{
    return m_comps;
}
