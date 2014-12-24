#ifndef SWEEPERGRAPHICS_HPP
#define SWEEPERGRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include <vector>

struct Tile
{
    sf::Vector2f size;
    sf::Vector2f texCoord;
};

class SweeperGraphics : public sf::Drawable, public sf::Transformable
{
public:
    bool init();
    void updateState(int** board, int status, double elapsed);
    void setBoardSize(sf::Vector2f boardSize);
    void setBoardNumbers(int** numbers);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    sf::Vector2f m_boardSize;
    int** m_boardNumbers;
    std::map<int, Tile> m_tileMap;
    sf::Texture m_tilesheet;
    sf::Texture m_numbersheet;
    sf::Texture m_minesheet;
    std::vector<sf::Vertex> m_tiles;
    std::vector<sf::Vertex> m_numbers;
    std::vector<sf::Vertex> m_mines;
};

#endif
