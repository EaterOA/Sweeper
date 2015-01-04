#include "gameconfig.hpp"
#include <cstdlib>

GameConfig config;

bool GameConfig::init()
{
    //Defaults for configuration not in config file
    std::map<std::string, std::string> defaults;
    defaults["board_width"] = "16";
    defaults["board_height"] = "16";
    defaults["mine_perc"] = "15";
    defaults["seethrough_mines"] = "0";
    load("config/config.txt", defaults);
    constrainInts();

    return true;
}

void GameConfig::reload()
{
    load("config/config.txt");
    constrainInts();
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
