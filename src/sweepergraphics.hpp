#ifndef SWEEPERGRAPHICS_HPP
#define SWEEPERGRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class SweeperGraphics : public sf::Drawable, public sf::Transformable
{
public:
    bool init();
    void updateState(int** board, int status, double elapsed);
    void setBoardSize(sf::Vector2f boardSize);
    void setBoardNumbers(int** numbers);
    void setBoardMines(bool** mines);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    sf::Vector2f m_boardSize;
    sf::RectangleShape m_background;
    sf::Texture m_tilesheet;
    sf::Texture m_numbersheet;
    sf::Texture m_minesheet;
    std::vector<sf::Vertex> m_tiles;
    std::vector<sf::Vertex> m_numbers;
    std::vector<sf::Vertex> m_mines;
};

#endif
