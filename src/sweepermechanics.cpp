#include "gameconfig.hpp"
#include "sweepermechanics.hpp"

bool SweeperMechanics::init()
{
    m_board = NULL;
    m_minefield = NULL;
    m_numfield = NULL;
    reset();
    return true;
}

void SweeperMechanics::reset()
{
    m_elapsed = 0;
}


void SweeperMechanics::start()
{
}

void SweeperMechanics::tick(const sf::Time &elapsed)
{
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
            if (r < pn)
            {
                minefield[i][j] = true;
            }
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
