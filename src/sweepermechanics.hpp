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
    sf::Vector2<int> getSize();
    int** getBoard();
    bool** getMinefield();
    int** getNumfield();
private:
    bool** generateMinefield(double p, int w, int h);
    int** generateNumfield(bool** minefield, int w, int h);

    sf::Vector2<int> m_size;
    bool** m_minefield;
    int** m_numfield;
    int** m_board;
};

#endif
