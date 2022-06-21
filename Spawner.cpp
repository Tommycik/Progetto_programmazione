//
// Created by tommy on 16/06/2022.
//

#include "Spawner.h"
#include "Dungeonarea.h"

void Spawner::spawn( const int numObstacle, const int numObject, const int numSafezone,
                    const int numBoss,  Dungeonarea &map) {

  Spawner::enemies.reserve(numObstacle);
  Spawner::safezones.reserve(numSafezone);
  Spawner::items.reserve(numObject);
  Spawner::bosses.reserve(numBoss);
  Spawner::teleports.reserve(numBoss);

  Dice itemTypeDice(3);
  Dice relPositionDispl(10);
    for(int i=0; i<numObject; i++) {
        Item* item;
        int effect=itemTypeDice.roll(1);
        if(effect==1) {
            item = new Item(1,1,1,"item",1);
        } else if(effect==2) {
            item = new Item(1,1,1,"item",2);
        }else{
            item = new Item(1,1,1,"item",3);
        }

        int flipSearch = 0;
        bool positionFound = false;
        int startX=map.getRand(0,map.getWidth());
        int startY=map.getRand(0,map.getHeight());
        int itemPositionX = startX;
        int itemPositionY = startY;
        while(!positionFound) {
            if (flipSearch%7==0) {
                itemPositionX = startX+1;
                itemPositionY = startY+1;
            }
            if(flipSearch%2) {
                itemPositionX += relPositionDispl.roll(1+flipSearch);
                itemPositionY += relPositionDispl.roll(1+flipSearch);
                flipSearch++;
            } else {
                itemPositionX -= relPositionDispl.roll(1+flipSearch);
                itemPositionY -= relPositionDispl.roll(1+flipSearch);
                flipSearch++;
            }
            if( itemPositionX<0 || itemPositionX>map.getWidth())
                itemPositionX = startX+1;
            if( itemPositionY<0 || itemPositionY>map.getHeight())
                itemPositionY = startY+1;
            positionFound = findFreeMapTile(itemPositionX, itemPositionY, map,&items,&enemies,&safezones,&bosses);
            if (itemPositionX == startX && itemPositionY == startY)
                positionFound = false;
        }
        item->setposX(itemPositionX);
        item->setposY(itemPositionY);
        items.push_back(item);
    }

    Dice BossTypeDice(3);
    bool port;
    for(int i=0; i<numBoss; i++) {
        Boss* boss;
        Object* teleport;
        int effect=itemTypeDice.roll(1);
        if(effect==1) {
            boss = new Boss(2,1,2,3,"boss",1);
        } else if(effect==2) {
            boss = new Boss(2,1,2,3,"boss",1);
        }else{
            boss = new Boss(2,1,2,3,"boss",1);
        }

        int flipSearch = 0;
        bool positionFound = false;
        int startX=map.getRand(0,map.getWidth());
        int startY=map.getRand(0,map.getHeight());
        int bossPositionX = startX;
        int bossPositionY = startY;
        while(!positionFound) {
            if (flipSearch%7==0) {
                bossPositionX = startX+1;
                bossPositionY = startY+1;
            }
            if(flipSearch%2) {
                bossPositionX += relPositionDispl.roll(1+flipSearch);
                bossPositionY += relPositionDispl.roll(1+flipSearch);
                flipSearch++;
            } else {
                bossPositionX -= relPositionDispl.roll(1+flipSearch);
                bossPositionY -= relPositionDispl.roll(1+flipSearch);
                flipSearch++;
            }
            if( bossPositionX<0 || bossPositionX>map.getWidth())
                bossPositionX = startX+1;
            if( bossPositionY<0 ||bossPositionY>map.getHeight())
                bossPositionY = startY+1;
            positionFound = findFreeMapTile(bossPositionX, bossPositionY, map, &items,&enemies,&safezones,&bosses);
            if (bossPositionX == startX && bossPositionY == startY)
                positionFound = false;
        }
        boss->setposX(bossPositionX);
        boss->setposY(bossPositionY);
        teleport=new Object(0,bossPositionX,bossPositionY,"teleport");
        bosses.push_back(boss);
        teleports.push_back(teleport);
    }

    for(int i=0; i<numSafezone; i++) {
        Object* safezone;
        safezone = new Object(1,2,2,"safezone");
        int flipSearch = 0;
        bool positionFound = false;
        int startX=map.getRand(0,map.getWidth());
        int startY=map.getRand(0,map.getHeight());
        int safezonePositionX = startX;
        int safezonePositionY = startY;
        while(!positionFound) {
            if (flipSearch%7==0) {
                safezonePositionX = startX+1;
                safezonePositionY = startY+1;
            }
            if(flipSearch%2) {
                safezonePositionX += relPositionDispl.roll(1+flipSearch);
                safezonePositionY += relPositionDispl.roll(1+flipSearch);
                flipSearch++;
            } else {
                safezonePositionX -= relPositionDispl.roll(1+flipSearch);
                safezonePositionY -= relPositionDispl.roll(1+flipSearch);
                flipSearch++;
            }
            if( safezonePositionX<0 || safezonePositionX>map.getWidth())
                safezonePositionX = startX+1;
            if( safezonePositionY<0 || safezonePositionY>map.getHeight())
                safezonePositionY = startY+1;
            positionFound = findFreeMapTile(safezonePositionX, safezonePositionY, map, &items,&enemies,&safezones,&bosses);
            if (safezonePositionX == startX && safezonePositionY == startY)
                positionFound = false;
            for (auto gc : bosses) {
                if (l2Distance(*gc,safezonePositionX,safezonePositionY)<30)
                    positionFound = false;}

        }
        safezone->setposX(safezonePositionX);
        safezone->setposY(safezonePositionY);
       safezones.push_back(safezone);
    }
    Dice enemyTypeDice(3);//todo fare in modo che i nemici peggio abbiano meno possibilità

    for(int i=0; i<numObstacle; i++) {
        Obstacle* enemy;
        int effect=itemTypeDice.roll(1);
        if(effect==1) {
            enemy = new Obstacle(5,1,8,2,"enemy",true);
        } else if(effect==2) {
            enemy = new Obstacle(5,1,8,2,"enemy",true);
        }else{
            enemy = new Obstacle(5,1,8,2,"enemy",true);
        }

        int flipSearch = 0;
        bool positionFound = false;
        int startX=map.getRand(0,map.getWidth());
        int startY=map.getRand(0,map.getHeight());
        int enemyPositionX = startX;
        int enemyPositionY = startY;
        while(!positionFound) {
            if (flipSearch%7==0) {
                enemyPositionX = startX+1;
                enemyPositionY = startY+1;
            }
            if(flipSearch%2) {
                enemyPositionX += relPositionDispl.roll(1+flipSearch);
                enemyPositionY += relPositionDispl.roll(1+flipSearch);
                flipSearch++;
            } else {
                enemyPositionX -= relPositionDispl.roll(1+flipSearch);
                enemyPositionY -= relPositionDispl.roll(1+flipSearch);
                flipSearch++;
            }
            if( enemyPositionX<0 || enemyPositionX>map.getWidth())
                enemyPositionX = startX+1;
            if( enemyPositionY<0 ||enemyPositionY>map.getHeight())
                enemyPositionY = startY+1;
            positionFound = findFreeMapTile(enemyPositionX, enemyPositionY, map, &items,&enemies,&safezones,&bosses);
            if (enemyPositionX == startX && enemyPositionY == startY)
                positionFound = false;
            for (auto gc : bosses) {
                if (l2Distance(*gc,enemyPositionX,enemyPositionY)<30)
                    positionFound = false;

            }
            for (auto gc : safezones) {
                if (l2Distance(*gc,enemyPositionX,enemyPositionY)<15)
                    positionFound = false;

            }
        }
        enemy->setposX(enemyPositionX);
        enemy->setposY(enemyPositionY);
        enemies.push_back(enemy);
    }



}

const std::vector<Obstacle *> &Spawner::getEnemies() const {
    return enemies;
}



const std::vector<Item *> &Spawner::getItems() const {
    return items;
}




const std::vector<Object *> &Spawner::getSafezones() const {
    return safezones;
}



const std::vector<Object *> &Spawner::getTeleports() const {
    return teleports;
}



const std::vector<Boss *> &Spawner::getBosses() const {
    return bosses;
}

Spawner::Spawner(int monsterNumber, int objectNumber, int safezoneNumber, int bossNumber) : monsterNumber(
        monsterNumber), objectNumber(objectNumber), safezoneNumber(safezoneNumber), bossNumber(bossNumber) {}




