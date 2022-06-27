//
// Created by tommy on 16/06/2022.
//

#include "Spawner.h"
#include "Dungeonarea.h"



 std::vector<Obstacle *> &Spawner::getEnemies()  {
    return enemies;
}



 std::vector<Item *> &Spawner::getItems()  {
    return items;
}




 std::vector<Object *> &Spawner::getSafezones() {
    return safezones;
}



 std::vector<Teleport *> &Spawner::getTeleports()  {
    return teleports;
}



 std::vector<Boss *> &Spawner::getBosses()  {
    return bosses;
}

Spawner::Spawner(int monsterNumber, int objectNumber, int safezoneNumber, int bossNumber) : monsterNumber(
        monsterNumber), objectNumber(objectNumber), safezoneNumber(safezoneNumber), bossNumber(bossNumber) {}


void Spawner::create() {
    enemies.reserve(monsterNumber);
    safezones.reserve(safezoneNumber);
    items.reserve(objectNumber);
    bosses.reserve(bossNumber);
    teleports.reserve(bossNumber);

    Dice itemTypeDice(3);

    for(int i=0; i<objectNumber; i++) {
        Item* item;
        int effect=itemTypeDice.roll(1);
        if(effect==1) {
            item = new Item(1,1,1,1);
        } else if(effect==2) {
            item = new Item(1,1,1,2);
        }else{
            item = new Item(1,1,1,3);
        }
        items.push_back(item);
    }

    Dice BossTypeDice(3);

    for(int i=0; i<bossNumber; i++) {
        Boss* boss;
        Teleport* teleport;
        int effect=BossTypeDice.roll(1);
        if(effect==1) {
            boss = new Boss(2,1,2,2,1);
        } else if(effect==2) {
            boss = new Boss(2,1,2,2,1);
        }else{
            boss = new Boss(2,1,2,2,1);
        }


        teleport=new Teleport(3,3);
        bosses.push_back(boss);
        teleports.push_back(teleport);
    }

    for(int i=0; i<safezoneNumber; i++) {
        Object* safezone;
        safezone = new Object(1,4,4);


        safezones.push_back(safezone);
    }

    Dice enemyTypeDice(3);//todo fare in modo che i nemici peggio abbiano meno possibilità

    for(int i=0; i<monsterNumber; i++) {
        Obstacle* enemy;
        int effect=enemyTypeDice.roll(1);
        if(effect==1) {
            enemy = new Obstacle(5,1,8,2,true);
        } else if(effect==2) {
            enemy = new Obstacle(5,1,8,2,true);
        }else{
            enemy = new Obstacle(5,1,8,2,true);
        }
        enemies.push_back(enemy);
    }
}
