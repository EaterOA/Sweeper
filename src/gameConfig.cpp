#include "gameConfig.hpp"
#include <cstdlib>

GameConfig config;

bool GameConfig::init()
{
    m_path = "config.txt";

    //Defaults for configuration not in config file
    std::map<std::string, std::string> defaults;
    defaults["board_width"] = "16";
    defaults["board_height"] = "16";
    defaults["mine_perc"] = "15";
    defaults["seethrough_mines"] = "0";
    load(m_path, defaults);
    constrainInts();

    return true;
}

bool GameConfig::reload()
{
    if (!load(m_path))
        return false;
    constrainInts();
    return true;
}

void GameConfig::constrainInts()
{
    // key, min, max
    std::string constraints[][3] = {
        {"board_width", "3", "100"},
        {"board_height", "3", "100"},
        {"mine_perc", "10", "90"},
        {"seethrough_mines", "0", "1"}
    };
    int elements = sizeof(constraints)/sizeof(*constraints);
    for (int i = 0; i < elements; i++) {
        int value = getInt(constraints[i][0]);
        int left = atoi(constraints[i][1].c_str());
        int right = atoi(constraints[i][2].c_str());
        if (value < left)
            setInt(constraints[i][0], left);
        else if (value > right)
            setInt(constraints[i][0], right);
    }
}

bool GameConfig::save()
{
    return Config::save(m_path);
}
