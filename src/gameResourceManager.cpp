#include "gameResourceManager.hpp"
#include "util.hpp"

GameResourceManager resource;

bool GameResourceManager::init()
{
    // loading necessary textures
    std::map<std::string, std::string> loadList;
    loadList["numbers"] = "img/numbersheet.png";
    loadList["numbers_outlined"] = "img/numbersheet_outlined.png";
    loadList["mine"] = "img/mine.png";
    loadList["tiles"] = "img/tilesheet.png";
    loadList["reload"] = "img/reload.png";
    for (std::map<std::string, std::string>::iterator iter = loadList.begin(); iter != loadList.end(); iter++)
        if (!loadTexture(iter->first, iter->second))
            return false;

    // set smooth for textures
    for (std::map<std::string, sf::Texture>::iterator iter = db_tex.begin(); iter != db_tex.end(); iter++)
        iter->second.setSmooth(true);

    // loading necessary fonts
    loadList = std::map<std::string, std::string>();
    for (std::map<std::string, std::string>::iterator iter = loadList.begin(); iter != loadList.end(); iter++)
        if (!loadFont(iter->first, iter->second))
            return false;

    return true;
}
