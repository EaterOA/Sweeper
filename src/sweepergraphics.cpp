#include "util.hpp"
#include "gameconfig.hpp"
#include "sweepergraphics.hpp"

bool SweeperGraphics::init()
{
    if (!m_tilesheet.loadFromFile("img/tilesheet.png") ||
        !m_numbersheet.loadFromFile("img/numbersheet.png"))
        return false;

    m_background.setSize(sf::Vector2f(800, 600));
    m_background.setFillColor(sf::Color(210, 210, 210));

    return true;
}

void SweeperGraphics::updateState(int** board, int status, double elapsed)
{
    unsigned w = m_boardSize.x,
             h = m_boardSize.y;
    for (unsigned r = 0; r < h; r++)
        for (unsigned c = 0; c < w; c++) {
            util::affixTexture(&m_tiles[4 * (r * w + c)],
                               sf::Vector2f(32 * board[r][c], 0),
                               sf::Vector2f(32, 32));
        }
}

void SweeperGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_background);
    states.texture = &m_tilesheet;
    target.draw(&m_tiles[0], m_tiles.size(), sf::Quads, states);
    states.texture = &m_numbersheet;
    target.draw(&m_numbers[0], m_numbers.size(), sf::Quads, states);
}

void SweeperGraphics::newBoard(sf::Vector2f size, bool** mines, int** num)
{
    unsigned w = size.x,
             h = size.y;

    m_boardSize = size;
    m_numbers = std::vector<sf::Vertex>(4 * w * h, sf::Vertex());
    m_tiles = std::vector<sf::Vertex>(4 * w * h, sf::Vertex());
    m_mines = std::vector<sf::Vertex>();

    for (unsigned r = 0; r < h; r++)
        for (unsigned c = 0; c < w; c++) {
            // affixing position and texture for minefield
            if (mines[r][c]) {
                for (int i = 0; i < 4; i++)
                    m_mines.push_back(sf::Vertex());
                util::affixPos(&m_mines[m_mines.size()-4],
                               sf::Vector2f(32 * c, 32 * r),
                               sf::Vector2f(32, 32),
                               1);
                util::affixTexture(&m_mines[m_mines.size()-4],
                                   sf::Vector2f(0, 0),
                                   sf::Vector2f(32, 32));
            }

            // affixing position and texture for numfield
            util::affixPos(&m_numbers[4 * (r * w + c)],
                           sf::Vector2f(32 * c, 32 * r),
                           sf::Vector2f(32, 32),
                           1);
            int tx = 32 * (num[r][c] % 3);
            int ty = 32 * (num[r][c] / 3);
            util::affixTexture(&m_numbers[4 * (r * w + c)],
                               sf::Vector2f(tx, ty),
                               sf::Vector2f(32, 32));

            // affixing position for board
            util::affixPos(&m_tiles[4 * (r * w + c)],
                           sf::Vector2f(32 * c, 32 * r),
                           sf::Vector2f(32, 32),
                           1);
        }
}
