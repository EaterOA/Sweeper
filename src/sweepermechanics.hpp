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
    void start();
    void tick(const sf::Time &elapsed);
    int** getBoard();
    bool** getMinefield();
    int** getNumfield();
    sf::Vector2f getBoardSize();
    int getStatus();
    double getElapsed();
private:
    bool** generateMinefield(double p, int w, int h);
    int** generateNumfield(bool** minefield, int w, int h);

    sf::Vector2f m_boardSize;
    bool** m_minefield;
    int** m_numfield;
    int** m_board;
    int m_status;
    double m_elapsed;
};

#endif
