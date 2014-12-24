#ifndef BATTLEMECHANICS_HPP
#define BATTLEMECHANICS_HPP

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
    sf::Vector2f getBoardSize();
    int getStatus();
    double getElapsed();
private:
    SweeperEngine* m_engine;
    int** m_board;
    int m_status;
    double m_elapsed;
};

#endif
