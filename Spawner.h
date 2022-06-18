//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_SPAWNER_H
#define MAIN_SPAWNER_H
#include <vector>
#include "Obstacle.h"
#include "Boss.h"
#include "Object.h"
#include "Item.h"
#include "Dungeonarea.h"

class Spawner {
public :
    void spawn(int startX, int startY, const int numObstacles,const int numObject,const int numSafezone,const int numBoss, const Dungeonarea &map);
private:
    int monsterNumber;
    int objectNumber;
    int safezoneNumber;
    int bossNumber;
    std::vector<Obstacle*> enemies;
    std::vector<Item*> items;
    std::vector<Object*> safezones;
    std::vector<Object*> teleports;
    std::vector<Boss*> bosses;
};


#endif //MAIN_SPAWNER_H
