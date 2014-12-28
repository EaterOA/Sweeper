#ifndef SWEEPERMECHANICS_HPP
#define SWEEPERMECHANICS_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class SweeperEngine;

class SweeperMechanics
{
public:
    bool init();
    void reset();
    int openTile(unsigned r, unsigned c);
    int triggerTile(unsigned r, unsigned c);
    int flagTile(unsigned r, unsigned c);
    sf::Vector2<unsigned> getSize();
    int** getBoard();
    bool** getMinefield();
    int** getNumfield();
private:
    bool** generateMinefield(double p, unsigned w, unsigned h);
    int** generateNumfield(bool** minefield, unsigned w, unsigned h);

    sf::Vector2<unsigned> m_size;
    bool** m_minefield;
    int** m_numfield;
    int** m_board;
};

#endif
