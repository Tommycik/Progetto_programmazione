//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_SPAWNER_H
#define MAIN_SPAWNER_H
#include <vector>
#include "Obstacle.h"
#include "Boss.h"
#include "Object.h"
#include "Dice.h"
#include "Item.h"
#include "Dungeonarea.h"
#include "Template.h"

class Spawner {
public :
    void spawn( const int numObstacles,const int numObject,const int numSafezone,const int numBoss,  Dungeonarea &map);

    const std::vector<Obstacle *> &getEnemies() const;



    const std::vector<Item *> &getItems() const;





    const std::vector<Object *> &getSafezones() const;



    const std::vector<Object *> &getTeleports() const;



    const std::vector<Boss *> &getBosses() const;



    Spawner(int monsterNumber, int objectNumber, int safezoneNumber, int bossNumber);


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
