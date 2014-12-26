#include "gameconfig.hpp"
#include "sweepermechanics.hpp"
#include <cstring>

bool SweeperMechanics::init()
{
    m_board = NULL;
    m_minefield = NULL;
    m_numfield = NULL;
    return true;
}

void SweeperMechanics::reset()
{
    delete m_board;
    delete m_minefield;
    delete m_numfield;
    m_elapsed = 0;
    m_boardSize.x = config.getInt("board_width");
    m_boardSize.y = config.getInt("board_height");
    double mineProb = config.getInt("mine_perc") / 100.0;
    m_minefield = generateMinefield(mineProb, m_boardSize.x, m_boardSize.y);
    m_numfield = generateNumfield(m_minefield, m_boardSize.x, m_boardSize.y);
    m_board = new int*[(int)m_boardSize.y];
    for (int i = 0; i < m_boardSize.y; i++) {
        m_board[i] = new int[(int)m_boardSize.x];
        memset(m_board[i], 0, sizeof(int) * m_boardSize.x);
    }
}

void SweeperMechanics::tick(const sf::Time &elapsed)
{
    m_elapsed += elapsed.asSeconds();
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

int SweeperMechanics::getStatus()
{
    return m_status;
}

sf::Vector2f SweeperMechanics::getBoardSize()
{
    return m_boardSize;
}

double SweeperMechanics::getElapsed()
{
    return m_elapsed;
}

bool** SweeperMechanics::generateMinefield(double p, int w, int h)
{
    int pn = p * 100000;
    bool** minefield = new bool*[h];
    for (int i = 0; i < h; i++)
    {
        minefield[i] = new bool[w];
        for (int j = 0; j < w; j++)
        {
            int r = rand() % 100000;
            minefield[i][j] = r < pn;
        }
    }
    return minefield;
}

int** SweeperMechanics::generateNumfield(bool** minefield, int w, int h)
{
    int** numfield = new int*[h];
    for (int i = 0; i < h; i++)
    {
        numfield[i] = new int[w];
        memset(numfield[i], 0, sizeof(int) * (unsigned)w);
        for (int j = 0; j < w; j++)
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
