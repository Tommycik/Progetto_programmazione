//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_SPAWNER_H
#define MAIN_SPAWNER_H

#include <vector>
#include "StaticDanger.h"
#include "FollowingEnemies.h"
#include "Dreadgen.h"
#include "Safezone.h"
#include "Dice.h"
#include "Item.h"
#include "Dungeonarea.h"
#include "Teleport.h"
#include <memory>

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
    void setMonsterNumber(int monsterNumber);
    void setBossNumber(int bossNumber);
    std::vector<std::unique_ptr<Obstacle>> &getEnemies() ;
    std::vector<std::unique_ptr<Item>> &getItems() ;
    std::vector<std::unique_ptr<Safezone>> &getSafezones();
    std::vector<std::unique_ptr<Teleport>> &getTeleports() ;
    std::vector<std::unique_ptr<Boss>> &getBosses() ;

private:

    std::string fileLine;
    std::ifstream op;
    int monsterNumber=0;
    int objectNumber=0;
    int safezoneNumber=0;
    int bossNumber=0;
    std::vector<std::unique_ptr<Obstacle>> enemies;
    std::vector<std::unique_ptr<Item>> items;
    std::vector<std::unique_ptr<Safezone>> safezones;
    std::vector<std::unique_ptr<Teleport>> teleports;
    std::vector<std::unique_ptr<Boss>> bosses;
};


#endif //MAIN_SPAWNER_H
