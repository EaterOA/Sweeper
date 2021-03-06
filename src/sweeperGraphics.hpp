#ifndef SWEEPERGRAPHICS_HPP
#define SWEEPERGRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class SweeperGraphics : public sf::Drawable, public sf::Transformable
{
public:
    bool init();
    void updateBoard(int** board, int status, bool pressing, bool triggering, sf::Vector2i loc);
    void newBoard(sf::Vector2i size, bool** mines, int** num);
    sf::Vector2i getTile(float x, float y);
    sf::Vector2f calculateSizeInPixels();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    int m_status;
    sf::Vector2i m_size;
    sf::RectangleShape m_background;
    std::vector<sf::Vertex> m_tiles;
    std::vector<sf::Vertex> m_numbers;
    std::vector<sf::Vertex> m_numbers_outlined;
    std::vector<sf::Vertex> m_mines;
};

#endif
