#ifndef SWEEPERMECHANICS_HPP
#define SWEEPERMECHANICS_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class SweeperEngine;

//flags: 0 = unmarked, 1 = marked, 2 = open, 3 = wrong
class SweeperMechanics
{
public:
    bool init();
    void reset();
    int openTile(int r, int c);
    int triggerTile(int r, int c);
    int flagTile(int r, int c);
    void markWrongTiles();
    sf::Vector2i getSize();
    int** getBoard();
    bool** getMinefield();
    int** getNumfield();
private:
    bool** generateMinefield(double p, int rows, int cols);
    int** generateNumfield(bool** minefield, int rows, int cols);

    sf::Vector2i m_size;
    bool** m_minefield;
    int** m_numfield;
    int** m_board;
    int m_opened, m_free;
};

#endif
