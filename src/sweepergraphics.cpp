#include "util.hpp"
#include "gameconfig.hpp"
#include "sweepergraphics.hpp"

bool SweeperGraphics::init()
{
    if (!m_tilesheet.loadFromFile("img/tilesheet.png") ||
        !m_numbersheet.loadFromFile("img/numbersheet.png") ||
        !m_minesheet.loadFromFile("img/mine.png"))
        return false;

    m_background.setSize(sf::Vector2f(800, 600));
    m_background.setFillColor(sf::Color(210, 210, 210));

    return true;
}

void SweeperGraphics::updateBoard(int** board, int status, bool pressing, bool triggering, sf::Vector2<int> loc)
{
    // updating state variables
    m_status = status;

    // retiling the board
    for (int r = 0; r < m_size.y; r++)
        for (int c = 0; c < m_size.x; c++) {
            int idx = 4 * (r * m_size.x + c);
            util::affixTexture(&m_tiles[idx],
                               sf::Vector2f(32.f * board[r][c], 0),
                               sf::Vector2f(32, 32));
        }

    // only allow unmarked tiles to be visible (when game is lost)
    int idx = 0;
    for (int r = 0; r < m_size.y && idx < (int)m_mines.size(); r++)
        for (int c = 0; c < m_size.x && idx < (int)m_mines.size(); c++) {
            if (r*32 == m_mines[idx].position.y &&
                c*32 == m_mines[idx].position.x) {
                sf::Vector2f tex(32, 32);
                if (board[r][c] != 0)
                    tex *= 0.f;
                util::affixTexture(&m_mines[idx],
                                   sf::Vector2f(32.f * board[r][c], 0),
                                   tex);
                idx += 4;
                }
        }

    // button clicking effects
    if (pressing) {
        int r = loc.y, c = loc.x;
        for (int i = r-1; i <= r+1; i++) {
            for (int j = c-1; j <= c+1; j++) {
                if (i < 0 || i >= m_size.y || j < 0 || j >= m_size.x)
                    continue;
                if (board[i][j] != 0)
                    continue;
                // only affect surrounding tiles if triggering
                if (!triggering && (i != r || j != c))
                    continue;
                util::affixTexture(&m_tiles[4 * (i * m_size.x + j)],
                                   sf::Vector2f(0, 32),
                                   sf::Vector2f(32, 32));
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
    if (m_status == 1) {
        states.texture = &m_minesheet;
        target.draw(&m_mines[0], m_mines.size(), sf::Quads, states);
    }
}

void SweeperGraphics::newBoard(sf::Vector2<int> size, bool** mines, int** num)
{
    m_size = size;
    m_tiles = std::vector<sf::Vertex>(4 * m_size.x * m_size.y, sf::Vertex());
    m_numbers = std::vector<sf::Vertex>(m_tiles.size());
    m_mines = std::vector<sf::Vertex>();

    for (int r = 0; r < m_size.y; r++)
        for (int c = 0; c < m_size.x; c++) {
            int idx = 4 * (r * m_size.x + c);

            // affixing position
            if (mines[r][c]) {
                for (int i = 0; i < 4; i++)
                    m_mines.push_back(sf::Vertex());
                util::affixPos(&m_mines[m_mines.size()-4],
                               sf::Vector2f(32.f * c, 32.f * r),
                               sf::Vector2f(32, 32),
                               1);
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
