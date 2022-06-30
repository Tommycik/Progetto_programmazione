//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_WORLD_H
#define MAIN_WORLD_H
#include <iostream>
#include <vector>
#include "Mario.h"
#include "Littlelight.h"
class World {
public:
    void savePlayer(int map,Mario &player,bool tutorialItem,bool tutorialSafezone,bool tutorialTeleport/*,int littleStatus*/);
    bool loadPlayer(int &mapIndex,Mario &player,bool &tutorialItem,bool &tutorialSafezone,bool &tutorialTeleport);
private:
    std::vector<std::string> areaSaves;

};

#endif //MAIN_WORLD_H
