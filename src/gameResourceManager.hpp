#ifndef GAMERESOURCEMANAGER_HPP
#define GAMERESOURCEMANAGER_HPP

#include "resourceManager.hpp"

class GameResourceManager: public ResourceManager
{
public:
    bool init();
};

extern GameResourceManager resource;

#endif
