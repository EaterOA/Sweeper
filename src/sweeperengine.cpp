#include "sweeperengine.hpp"
#include <ctime>

SweeperEngine::SweeperEngine(int x, int y)
{
    srand((unsigned)time(NULL));

    //let p be probability between 0.1 and 0.2
    int p = (rand() % 5000) + (rand() % 5000) + 20000; //out of 100000

    SweeperEngine(x, y, p / 100000.0);
}

SweeperEngine::SweeperEngine(int x, int y, double p)
{
    int pn = p * 100000;
    minefield = new bool*[x];
    for (int i = 0; i < x; i++)
    {
        minefield[i] = new bool[y];
        for (int j = 0; j < y; j++)
        {
            int r = rand() % 100000;
            if (r < pn)
            {
                minefield[i][j] = true;
            }
        }
    }

    numfield = new int*[x];
    for (int i = 0; i < x; i++)
    {
        numfield[i] = new int[y];
        for (int j = 0; j < y; j++)
        {
            if (i > 0)
            {
                numfield[i][j] = numfield[i][j] + minefield[i-1][j];
                if (j > 0)
                    numfield[i][j] = numfield[i][j] + minefield[i-1][j-1];
                if (j < y - 1)
                    numfield[i][j] = numfield[i][j] + minefield[i-1][j+1];
            }
            if (i < x - 1)
            {
                numfield[i][j] = numfield[i][j] + minefield[i+1][j];
                if (j > 0)
                    numfield[i][j] = numfield[i][j] + minefield[i+1][j-1];
                if (j < y - 1)
                    numfield[i][j] = numfield[i][j] + minefield[i+1][j+1];
            }
            if (j > 0)
                numfield[i][j] = numfield[i][j] + minefield[i][j-1];
            if (j < y - 1)
                numfield[i][j] = numfield[i][j] + minefield[i][j+1];
            numfield[i][j] = numfield[i][j] + minefield[i][j];
        }
    }
}

const bool** SweeperEngine::getMinefield()
{
    return minefield;
}

const int** SweeperEngine::getNumfield()
{
    return numfield;
}

int SweeperEngine::getX()
{
    return dimX;
}

int SweeperEngine::getY()
{
    return dimY;
}

