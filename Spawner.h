//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_SPAWNER_H
#define MAIN_SPAWNER_H

#include <vector>
#include "Obstacle.h"
#include "Boss.h"
#include "Safezone.h"
#include "Dice.h"
#include "Item.h"
#include "Dungeonarea.h"
#include "Teleport.h"

class Spawner {

public :

    Spawner(bool loading ,Dungeonarea&map,int monsterNumber, int objectNumber, int safezoneNumber, int bossNumber=1);
    ~Spawner();

    void create(bool loading,Dungeonarea &map);
    void saveVectors(std::string fileName,std::string name,int Bosses,int Items,int Enemies,int Safezones);
    bool loadVectors(std::string fileName,std::string name,Dungeonarea &map);
    int getMonsterNumber() const;
    int getObjectNumber() const;
    int getSafezoneNumber() const;
    int getBossNumber() const;
    std::vector<Obstacle *> &getEnemies() ;
    std::vector<Item *> &getItems() ;
    std::vector<Safezone *> &getSafezones();
    std::vector<Teleport *> &getTeleports() ;
    std::vector<Boss *> &getBosses() ;

private:

    std::ifstream op;
    int monsterNumber=0;
    int objectNumber=0;
    int safezoneNumber=0;
    int bossNumber=0;
    std::vector<Obstacle*> enemies;
    std::vector<Item*> items;
    std::vector<Safezone*> safezones;
    std::vector<Teleport*> teleports;
    std::vector<Boss*> bosses;

};


#endif //MAIN_SPAWNER_H
