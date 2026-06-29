#include "kbhit.hpp"
#include "Entity.hpp"
#include "Location.hpp"

using namespace std;

void camera(const Entity& enty, const World& wrld)
{
    short index = -1;

    for(short n = 0; n < wrld.locs.size(); ++n)
    {
        if(enty.type == "Player" && enty.loc == wrld.locs[n].name)
        {
            index = n;
            break;
        }
    }

    if(enty.type == "Player" && wrld.locs[index].active && index != -1)
    {
        if(enty.posX < (enty.cam.view / 2)) enty.cam.angleX = 0;
        else if(enty.posX > (wrld.locs[index].sizeX - enty.cam.view / 2)) enty.cam.angleX = wrld.locs[index].sizeX - enty.cam.view;
        else enty.cam.angleX = enty.posX - enty.cam.view / 2;

        if(enty.posY < (enty.cam.view / 2)) enty.cam.angleY = 0;
        else if(enty.posY > (wrld.locs[index].sizeY - enty.cam.view / 2)) enty.cam.angleY = wrld.locs[index].sizeY - enty.cam.view;
        else enty.cam.angleY = enty.posY - enty.cam.view / 2;

        for(short i = 0; i < enty.cam.view; ++i)
        {
            for(short j = 0; j < enty.cam.view; ++j)
            {
                if(enty.posY == i && enty.posX == j) cout << "\x1b[" << enty.color << "m" << enty.symbol << "\x1b[0m";
                else cout << "\x1b[" << wrld.locs[index].colorGrid[i][j] << "m" << wrld.locs[index].coreGrid[i][j] << "\x1b[0m";
            }
        }
    }
}

int World::load()
{
    ifstream listFile("world/List.txt");

    if(!listFile)
    {
        cout << "\x1b[32m" << "File \'world/List.txt\' not found..." << endl;
        return 1;
    }


    return 0;
}
