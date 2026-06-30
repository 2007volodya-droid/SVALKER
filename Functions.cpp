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
            if(enty.type == "Player" && wrld.locs[index].active && index != -1)
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
    short i = 0;

    if(!listFile)
    {
        cout << "\x1b[32m" << "File \'world/List.txt\' not found..." << endl;
        return 1;
    }
    else
    {
        std::string name, address;

        while(listFile >> name >> address)
        {
            for(short j = 0; j < locs.at(i).obj.size(); ++j)
            {
                if(locs.at(i).obj.at(j)->loc == name && locs.at(i).obj.at(j)->type == "Player") break;
            }
            locs.at(i).name = name;
            i++;
        };

        ifstream locFile(address);

        if(!listFile)
        {
            cout << "\x1b[32m" << "File \'world/" << address << "\' not found..." << endl;
            return 1;
        }
        else
        {
            std::string line;
            while(getline(locFile, line))
            {
                if(line == "Size_map")
                {
                    locFile >> locs.at(i).sizeX >> locs.at(i).sizeY;
                }

                if(line == "Pos_map")
                {
                    locFile >> locs.at(i).posX >> locs.at(i).posY;
                }

                if(line == "Core_start")
                {
                    for(short n = 0; n <= locs.at(i).sizeY; ++n)
                    {
                        getline(locFile, line);

                        for(short m = 0; m <= locs.at(i).sizeX; ++m)
                        {
                            if((m < locs.at(i).sizeX && line.at(m) == '\0') || (m == locs.at(i).sizeX && line.at(m) != '\0'))
                            {
                                mapCheck = 0;
                                return 1;
                            }
                            else
                            {
                                locs.at(i).coreGrid.push_back(line);
                            }
                        }

                        if(n == locs.at(i).sizeY && line != "Core_end")
                        {
                            mapCheck = 0;
                            return 1;
                        }
                    }
                }

                if(line == "Color_start")
                {
                    short temp;

                    for(short n = 0; n <= locs.at(i).sizeY - 1; ++n)
                    {
                        for(short m = 0; m <= locs.at(i).sizeX - 1; ++m)
                        {
                            locFile >> temp;

                            temp >> locs.at(i).colorGrid.at(n).at(m);
                        }
                    }

                    for(short i = 0; i <= locs.at(i).sizeY - 1; ++i)
                    {
                        if(locs.at(i).colorGrid.at(i).size() < locs.at(i).sizeX - 1)
                        {
                            mapCheck = 0;
                            return 1;
                        }

                        if((i < locs.at(i).sizeY - 1 && locs.at(i).colorGrid.size()) || (i < locs.at(i).sizeY - 1 && !locs.at(i).colorGrid.size()))
                        {
                            mapCheck = 0;
                            return 1;
                        }
                    }
                }


            };
        }
    }



    return 0;
}
