#include "app.hpp"
#include "sweeper.hpp"
#include "util.hpp"
#include "sweeperBoard.hpp"
#include "reloader.hpp"
#include "slider.hpp"
#include "gameConfig.hpp"

bool Sweeper::init()
{
    // Board
    SweeperBoard* board = new SweeperBoard();
    board->init(this);
    // Reload button
    Reloader* reload = new Reloader();
    reload->init(this);
    reload->setSize(sf::Vector2f(50, 50));
    // Mine frequency slider
    Slider* mf = new Slider();
    mf->init(this, "Mine frequency");
    mf->setBounds(20, 90);
    mf->setSize(sf::Vector2f(140, 40));
    mf->setValue(config.getInt("mine_perc"));
    // Rows slider
    Slider* r = new Slider();
    r->init(this, "Rows");
    r->setBounds(8, 30);
    r->setSize(sf::Vector2f(100, 40));
    r->setValue(config.getInt("board_height"));
    // Columns slider
    Slider* c = new Slider();
    c->init(this, "Columns");
    c->setBounds(8, 30);
    c->setSize(sf::Vector2f(100, 40));
    c->setValue(config.getInt("board_width"));

    m_comps.push_back(board);
    m_comps.push_back(reload);
    m_comps.push_back(mf);
    m_comps.push_back(r);
    m_comps.push_back(c);

    adjustWindow();

    return true;
}

void Sweeper::adjustWindow()
{
    sf::Vector2f m_space(20, 20);
    int right = 0, bottom = 0;
    for (int i = 0; i < (int)m_comps.size(); i++) {
        switch (i) {
            case 0:
                m_comps[i]->setPosition(m_space);
                break;
            case 1:
                m_comps[i]->setPosition(sf::Vector2f(m_space.x * 2 + m_comps[0]->getSize().x, m_space.y));
                break;
            case 2:
                m_comps[i]->setPosition(sf::Vector2f(m_space.x * 2 + m_comps[0]->getSize().x, m_space.y * 2 + m_comps[1]->getSize().y));
                break;
            case 3:
                m_comps[i]->setPosition(sf::Vector2f(m_space.x * 2 + m_comps[0]->getSize().x, m_space.y * 3 + m_comps[1]->getSize().y + m_comps[2]->getSize().y));
                break;
            case 4:
                m_comps[i]->setPosition(sf::Vector2f(m_space.x * 2 + m_comps[0]->getSize().x, m_space.y * 3.2 + m_comps[1]->getSize().y + m_comps[2]->getSize().y + m_comps[3]->getSize().y));
                break;
            default:
                break;
        }
        int compRight = m_comps[i]->getPosition().x + m_comps[i]->getSize().x;
        int compBottom = m_comps[i]->getPosition().y + m_comps[i]->getSize().y;
        right = MAX(right, compRight);
        bottom = MAX(bottom, compBottom);
    }
    m_wsize.x = m_space.x + right;
    m_wsize.y = m_space.y + bottom;

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
