#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Object
{
public:
    short posX, posY, color;
    char symbol;
    std::string name, type, loc;

    virtual void update();
};

class Item: public Object
{
    short buf, unbuf;
    float mass;

    void update() override;
};

class Inventory
{
    float MAX_mass;
    std::vector<Item> items;
};

class Camera
{
public:
    mutable short angleX, angleY;
    const short view = 15;
};

class Entity: public Object
{
public:
    short oldX, oldY, healthPoint, arrmorPoint, energyPoint;
    std::vector<char> effects;

    Inventory intvry;
    Camera cam;

    void update() override;
};
