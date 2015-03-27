#ifndef GAMECONFIG_HPP
#define GAMECONFIG_HPP

#include "config.hpp"

class GameConfig: public Config
{
public:
    bool init();
    bool reload();
    bool save();
private:
    void constrainInts();

    std::string m_path;
};

extern GameConfig config;

#endif
