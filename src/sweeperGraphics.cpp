#include "util.hpp"
#include "gameConfig.hpp"
#include "gameResourceManager.hpp"
#include "sweeperGraphics.hpp"

bool SweeperGraphics::init()
{
    m_background.setSize(sf::Vector2f(800, 600));
    m_background.setFillColor(sf::Color(210, 210, 210));
    return true;
}

void SweeperGraphics::updateBoard(int** board, int status, bool pressing, bool triggering, sf::Vector2i loc)
{
    // updating state variables
    m_status = status;

    // retiling the board
    for (int r = 0; r < m_size.y; r++)
        for (int c = 0; c < m_size.x; c++) {
            int idx = 4 * (r * m_size.x + c);
            util::affixTexture(&m_tiles[idx],
                               sf::Vector2f(board[r][c], 0) * 32.f,
                               sf::Vector2f(32, 32));
        }

    // only allow unmarked mines to be visible (when game is lost)
    for (int i = 0; i < (int)m_mines.size(); i += 4) {
        int r = m_mines[i].position.y/32,
            c = m_mines[i].position.x/32;
        sf::Color color = sf::Color::Transparent;
        if (status == 1 && board[r][c] == 0)
            color = sf::Color::White;
        util::applyColor(&m_mines[i], color);
        if (!config.getInt("seethrough_mines"))
            color = sf::Color::Transparent;
        util::applyColor(&m_numbers_outlined[i], color);
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

void SweeperGraphics::adjustWindow(sf::RenderWindow &w)
{
    sf::Vector2u wsize;
    wsize.x = 32 * m_size.x;
    wsize.y = 32 * m_size.y;
    sf::View view(sf::FloatRect(0, 0, wsize.x, wsize.y));
    w.setView(view);
    w.setSize(wsize);
}

void SweeperGraphics::updateTimer(double elapsed)
{
}

void SweeperGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_background);
    states.texture = &resource.getTexture("tiles");
    target.draw(&m_tiles[0], m_tiles.size(), sf::Quads, states);
    states.texture = &resource.getTexture("numbers");
    target.draw(&m_numbers[0], m_numbers.size(), sf::Quads, states);
    states.texture = &resource.getTexture("mine");
    target.draw(&m_mines[0], m_mines.size(), sf::Quads, states);
    states.texture = &resource.getTexture("numbers_outlined");
    target.draw(&m_numbers_outlined[0], m_numbers_outlined.size(), sf::Quads, states);
}

void SweeperGraphics::newBoard(sf::Vector2i size, bool** mines, int** num)
{
    m_size = size;
    m_tiles = std::vector<sf::Vertex>(4 * m_size.x * m_size.y, sf::Vertex());
    m_numbers = std::vector<sf::Vertex>(m_tiles.size());
    m_mines = std::vector<sf::Vertex>();
    m_numbers_outlined = std::vector<sf::Vertex>();

    for (int r = 0; r < m_size.y; r++)
        for (int c = 0; c < m_size.x; c++) {
            int idx = 4 * (r * m_size.x + c);

            // affixing position and texture for minefield
            if (mines[r][c]) {
                for (int i = 0; i < 4; i++)
                    m_mines.push_back(sf::Vertex());
                util::affixPos(&m_mines[m_mines.size()-4],
                               sf::Vector2f(c, r) * 32.f,
                               sf::Vector2f(32, 32),
                               1);
                util::affixTexture(&m_mines[m_mines.size()-4],
                                   sf::Vector2f(0, 0),
                                   sf::Vector2f(32, 32));
            }

            // affixing position and texture for numfield
            util::affixPos(&m_numbers[idx],
                           sf::Vector2f(c, r) * 32.f,
                           sf::Vector2f(32, 32),
                           1);
            float tx = num[r][c] % 3;
            float ty = num[r][c] / 3;
            util::affixTexture(&m_numbers[idx],
                               sf::Vector2f(tx, ty) * 32.f,
                               sf::Vector2f(32, 32));

            // affixing position and texture for outlined numfield
            if (mines[r][c]) {
                for (int i = 0; i < 4; i++)
                    m_numbers_outlined.push_back(sf::Vertex());
                util::affixPos(&m_numbers_outlined[m_numbers_outlined.size()-4],
                               sf::Vector2f(c, r) * 32.f,
                               sf::Vector2f(32, 32),
                               1);
                util::affixTexture(&m_numbers_outlined[m_numbers_outlined.size()-4],
                                   sf::Vector2f(tx, ty) * 32.f,
                                   sf::Vector2f(32, 32));
            }

            // affixing position for board
            util::affixPos(&m_tiles[idx],
                           sf::Vector2f(c, r) * 32.f,
                           sf::Vector2f(32, 32),
                           1);
        }
}

sf::Vector2i SweeperGraphics::getTile(float x, float y)
{
    sf::Vector2i tile(x/32, y/32);
    sf::Vector2i noTile(-1, -1);
    if (tile.x >= m_size.x || tile.y >= m_size.y)
        return noTile;
    return tile;
}
