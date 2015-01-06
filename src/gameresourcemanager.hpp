#ifndef GAMERESOURCEMANAGER_HPP
#define GAMERESOURCEMANAGER_HPP

#include "resourcemanager.hpp"

class GameResourceManager: public ResourceManager
{
public:
    bool init();
};

extern GameResourceManager resource;

#endif 