#include "gameconfig.hpp"

GameConfig config;

bool GameConfig::init()
{
    //Defaults for configuration not in config file
    std::map<std::string, std::string> defaults;
    defaults["board_width"] = "16";
    defaults["board_height"] = "16";
    defaults["mine_perc"] = "15";
    load("config/config.txt", defaults);

    //Overriding certain internal configurations
    std::map<std::string, std::string> overrides;
    load(overrides);

    return true;
}

