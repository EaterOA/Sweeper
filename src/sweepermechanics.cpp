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

int SweeperMechanics::openTile(unsigned r, unsigned c)
{
    if(m_board[r][c] == 0)
    {
        if(m_minefield[r][c])
        {
            return 1; 
        }
        else
        {
            m_board[r][c] = 2;
        }
    }

    return 0; // game continue
}

int SweeperMechanics::triggerTile(unsigned r, unsigned c)
{
    int flags = 0;
    for(int i = (int)r - 1; i <= (int)r + 1; i++)
    {
        for(int j = (int)c - 1; j <= (int)c + 1; j++)
        {
            if(i >= 0 && i < (int)m_size.y
              && j >= 0 && j < (int)m_size.x
              && m_board[i][j] == 1)
            {
                flags++;
            }
        }
    }

    if(flags == m_numfield[r][c])
    {
        for(int i = (int)r - 1; i <= (int)r + 1; i++)
        {
            for(int j = (int)c - 1; j <= (int)c + 1; j++)
            {
                if(i >= 0 && i < (int)m_size.y
                  && j >= 0 && j < (int)m_size.x
                  && m_board[i][j] == 0)
                { 
                    int res = openTile((unsigned)i, (unsigned)j);
                    if(res == 1)
                        return 1; 
                }
            }
        }               
    }

    return 0; // game continue
}

int SweeperMechanics::flagTile(unsigned r, unsigned c)
{ 
    if(m_board[r][c] == 0)
        m_board[r][c] = 1;
    else if(m_board[r][c] == 1)
        m_board[r][c] = 0;
    
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
