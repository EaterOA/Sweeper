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

void SweeperGraphics::updateBoard(int** board, int status, bool pressing, bool triggering, sf::Vector2<int> loc)
{
    for (int r = 0; r < m_size.y; r++)
        for (int c = 0; c < m_size.x; c++) {
            int idx = 4 * (r * m_size.x + c);
            util::affixTexture(&m_tiles[idx],
                               sf::Vector2f(32.f * board[r][c], 0),
                               sf::Vector2f(32, 32));
        }

    if (pressing) {
        int r = loc.y, c = loc.x;
        if (board[r][c] == 0) {
            util::affixTexture(&m_tiles[4 * (r * m_size.x + c)],
                               sf::Vector2f(0, 32),
                               sf::Vector2f(32, 32));
        }
        if (triggering) {
            int offset[][2] = {{-1,-1},{0,-1},{1,-1},
                                {-1,0},{1,0},
                                {-1,1},{0,1},{1,1}};
            for (int i = 0; i < 8; i++) {
                int nr = r + offset[i][0],
                    nc = c + offset[i][1];
                if (nr >= 0 && nr < m_size.y && nc >= 0 && nc < m_size.x &&
                    board[nr][nc] == 0) {
                    util::affixTexture(&m_tiles[4 * (nr * m_size.x + nc)],
                                       sf::Vector2f(0, 32),
                                       sf::Vector2f(32, 32));
                }
            }
        }
    }
}

void SweeperGraphics::updateTimer(double elapsed)
{
}

void SweeperGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_background);
    states.texture = &m_tilesheet;
    target.draw(&m_tiles[0], m_tiles.size(), sf::Quads, states);
    states.texture = &m_numbersheet;
    target.draw(&m_numbers[0], m_numbers.size(), sf::Quads, states);
}

void SweeperGraphics::newBoard(sf::Vector2<int> size, bool** mines, int** num)
{
    m_size = size;
    m_numbers = std::vector<sf::Vertex>(4 * m_size.x * m_size.y, sf::Vertex());
    m_tiles = std::vector<sf::Vertex>(4 * m_size.x * m_size.y, sf::Vertex());
    m_mines = std::vector<sf::Vertex>();

    for (int r = 0; r < m_size.y; r++)
        for (int c = 0; c < m_size.x; c++) {
            int idx = 4 * (r * m_size.x + c);

            // affixing position and texture for minefield
            if (mines[r][c]) {
                for (int i = 0; i < 4; i++)
                    m_mines.push_back(sf::Vertex());
                util::affixPos(&m_mines[m_mines.size()-4],
                               sf::Vector2f(32.f * c, 32.f * r),
                               sf::Vector2f(32, 32),
                               1);
                util::affixTexture(&m_mines[m_mines.size()-4],
                                   sf::Vector2f(0, 0),
                                   sf::Vector2f(32, 32));
            }

            // affixing position and texture for numfield
            util::affixPos(&m_numbers[idx],
                           sf::Vector2f(32.f * c, 32.f * r),
                           sf::Vector2f(32, 32),
                           1);
            float tx = 32.f * (num[r][c] % 3);
            float ty = 32.f * (num[r][c] / 3);
            util::affixTexture(&m_numbers[idx],
                               sf::Vector2f(tx, ty),
                               sf::Vector2f(32, 32));

            // affixing position for board
            util::affixPos(&m_tiles[idx],
                           sf::Vector2f(32.f * c, 32.f * r),
                           sf::Vector2f(32, 32),
                           1);
        }
}

sf::Vector2<int> SweeperGraphics::getTile(float x, float y)
{
    sf::Vector2<int> tile(x/32, y/32);
    sf::Vector2<int> noTile(-1, -1);
    if (tile.x >= m_size.x || tile.y >= m_size.y)
        return noTile;
    return tile;
}
