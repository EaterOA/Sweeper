#ifndef SENGINE_HPP
#define SENGINE_HPP

class SweeperEngine
{
    public:
        SweeperEngine(int x, int y); //default minefield generation
        SweeperEngine(int x, int y, double p); //generate with prob p
        bool** getMinefield();
        int** getNumfield();
        int getX();
        int getY();

    private:
        bool** minefield;
        int** numfield;
        int dimX;
        int dimY;
};

#endif
