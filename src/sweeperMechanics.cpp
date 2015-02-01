#include "gameConfig.hpp"
#include "sweeperMechanics.hpp"
#include "util.hpp"

using namespace std;

bool SweeperMechanics::init()
{
    m_board = NULL;
    m_minefield = NULL;
    m_numfield = NULL;
    return true;
}

void SweeperMechanics::reset()
{
    m_opened = 0;
    m_free = 0;
    util::free2D(m_board);
    util::free2D(m_minefield);
    util::free2D(m_numfield);
    m_size.x = config.getInt("board_width");
    m_size.y = config.getInt("board_height");
    double mineProb = config.getInt("mine_perc") / 100.0;
    m_minefield = generateMinefield(mineProb, m_size.y, m_size.x);
    m_numfield = generateNumfield(m_minefield, m_size.y, m_size.x);
    m_board = util::alloc2Dint(m_size.y, m_size.x);
}

int SweeperMechanics::openTile(int r, int c)
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
            m_opened++;
            if(m_opened == m_free)
                return 2;
        }
    }

    return 0; // game continue
}

int SweeperMechanics::triggerTile(int r, int c)
{
    int flags = 0;
    for(int i = r - 1; i <= r + 1; i++)
    {
        for(int j = c - 1; j <= c + 1; j++)
        {
            if(i >= 0 && i < m_size.y
              && j >= 0 && j < m_size.x
              && m_board[i][j] == 1)
            {
                flags++;
            }
        }
    }

    int res = 0;
    if(flags == m_numfield[r][c])
    {
        for(int i = r - 1; i <= r + 1; i++)
        {
            for(int j = c - 1; j <= c + 1; j++)
            {
                if(i >= 0 && i < m_size.y
                  && j >= 0 && j < m_size.x
                  && m_board[i][j] == 0)
                {
                    int temp = openTile(i, j);
                    if (res == 0)
                        res = temp;
                }
            }
        }
    }

    return res;
}

int SweeperMechanics::flagTile(int r, int c)
{
    if(m_board[r][c] == 0)
        m_board[r][c] = 1;
    else if(m_board[r][c] == 1)
        m_board[r][c] = 0;

    return 0;
}

void SweeperMechanics::markWrongTiles()
{
    for (int r = 0; r < m_size.y; r++)
    for (int c = 0; c < m_size.x; c++)
    {
        //if no mine, but we mark
        if (!m_minefield[r][c] && m_board[r][c] == 1)
        {
            m_board[r][c] = 3;
        }
    }
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

sf::Vector2i SweeperMechanics::getSize()
{
    return m_size;
}

bool** SweeperMechanics::generateMinefield(double p, int rows, int cols)
{
    int pn = p * RAND_MAX;
    bool** minefield = util::alloc2Dbool(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int r = rand();
            minefield[i][j] = r < pn;
            m_free += r >= pn;
        }
    }
    return minefield;
}

int** SweeperMechanics::generateNumfield(bool** minefield, int rows, int cols)
{
    int** numfield = util::alloc2Dint(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i > 0)
            {
                numfield[i][j] = numfield[i][j] + minefield[i-1][j];
                if (j > 0)
                    numfield[i][j] = numfield[i][j] + minefield[i-1][j-1];
                if (j < cols - 1)
                    numfield[i][j] = numfield[i][j] + minefield[i-1][j+1];
            }
            if (i < rows - 1)
            {
                numfield[i][j] = numfield[i][j] + minefield[i+1][j];
                if (j > 0)
                    numfield[i][j] = numfield[i][j] + minefield[i+1][j-1];
                if (j < cols - 1)
                    numfield[i][j] = numfield[i][j] + minefield[i+1][j+1];
            }
            if (j > 0)
                numfield[i][j] = numfield[i][j] + minefield[i][j-1];
            if (j < cols - 1)
                numfield[i][j] = numfield[i][j] + minefield[i][j+1];
            numfield[i][j] = numfield[i][j] + minefield[i][j];
        }
    }
    return numfield;
}
