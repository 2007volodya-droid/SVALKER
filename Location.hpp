#pragma once

#include "Entity.hpp"

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <memory>

class Location
{
public:
    bool active = 0;
    short sizeX, sizeY;
    unsigned short  posX, posY;
    std::string name;
    std::vector<std::string> coreGrid;
    std::vector<std::vector<short>> colorGrid;

    std::vector<std::unique_ptr<Object>> obj;
};

class World
{
public:
    bool mapCheck;
    std::vector<Location> locs;

    int load();
};
