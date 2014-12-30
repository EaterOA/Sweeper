#ifndef GAMECONFIG_HPP
#define GAMECONFIG_HPP

#include "config.hpp"

class GameConfig: public Config
{
public:
    bool init();
};

extern GameConfig config;

#endif
