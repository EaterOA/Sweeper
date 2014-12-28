#include "gameconfig.hpp"
#include "sweepermechanics.hpp"
#include "util.hpp"

bool SweeperMechanics::init()
{
    m_board = NULL;
    m_minefield = NULL;
    m_numfield = NULL;
    return true;
}

void SweeperMechanics::reset()
{
    util::free2D(m_board);
    util::free2D(m_minefield);
    util::free2D(m_numfield);
    m_size.x = (unsigned)config.getInt("board_width");
    m_size.y = (unsigned)config.getInt("board_height");
    double mineProb = config.getInt("mine_perc") / 100.0;
    m_minefield = generateMinefield(mineProb, m_size.x, m_size.y);
    m_numfield = generateNumfield(m_minefield, m_size.x, m_size.y);
    m_board = util::alloc2Dint(m_size.x, m_size.y);
}

int openTile(unsigned r, unsigned c)
{
    return 0; // game continue
}

int triggerTile(unsigned r, unsigned c)
{
    return 0; // game continue
}

int flagTile(unsigned r, unsigned c)
{
    return 0;
}

int** SweeperMechanics::getBoard()
{
    return m_board;
}

bool** SweeperMechanics::getMinefield()
{
    return m_minefield;
}

int** SweeperMechanics::getNumfield()
{
    return m_numfield;
}

sf::Vector2<unsigned> SweeperMechanics::getSize()
{
    return m_size;
}

bool** SweeperMechanics::generateMinefield(double p, unsigned w, unsigned h)
{
    int pn = p * 100000;
    bool** minefield = util::alloc2Dbool(h, w);
    for (unsigned i = 0; i < h; i++)
    {
        for (unsigned j = 0; j < w; j++)
        {
            int r = rand() % 100000;
            minefield[i][j] = r < pn;
        }
    }
    return minefield;
}

int** SweeperMechanics::generateNumfield(bool** minefield, unsigned w, unsigned h)
{
    int** numfield = util::alloc2Dint(h, w);
    for (unsigned i = 0; i < h; i++)
    {
        for (unsigned j = 0; j < w; j++)
        {
            if (i > 0)
            {
                numfield[i][j] = numfield[i][j] + minefield[i-1][j];
                if (j > 0)
                    numfield[i][j] = numfield[i][j] + minefield[i-1][j-1];
                if (j < w - 1)
                    numfield[i][j] = numfield[i][j] + minefield[i-1][j+1];
            }
            if (i < h - 1)
            {
                numfield[i][j] = numfield[i][j] + minefield[i+1][j];
                if (j > 0)
                    numfield[i][j] = numfield[i][j] + minefield[i+1][j-1];
                if (j < w - 1)
                    numfield[i][j] = numfield[i][j] + minefield[i+1][j+1];
            }
            if (j > 0)
                numfield[i][j] = numfield[i][j] + minefield[i][j-1];
            if (j < w - 1)
                numfield[i][j] = numfield[i][j] + minefield[i][j+1];
            numfield[i][j] = numfield[i][j] + minefield[i][j];
        }
    }
    return numfield;
}
