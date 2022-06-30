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
#include "Teleport.h"
class Spawner {
public :





    Spawner();
    explicit Spawner(int monsterNumber, int objectNumber, int safezoneNumber, int bossNumber);

    ~Spawner() {

    }

    void create();
    std::vector<Obstacle *> &getEnemies() ;

    std::vector<Item *> &getItems() ;

    std::vector<Object *> &getSafezones();

    std::vector<Teleport *> &getTeleports() ;

    std::vector<Boss *> &getBosses() ;
    template<typename T>

    void spawn(  Dungeonarea &map,T* Vector=nullptr) {
        int i=0;
        bool positionFound = false;
        int itemPositionX = 0;
        int itemPositionY = 0;
        TileType control=TileType::Unused;
        for (auto gc: *Vector) {

            positionFound = false;
            std::cout << "# auto \t" ;

            while (true) {
                std::cout << "# while \t" ;
                itemPositionX = 0;
                itemPositionY = 0;
                //control=TileType::Unused;
                map.setOldseed(map.getOldseed()+map.getRand(0,1000));
                itemPositionX = map.getRand(0, (map.getWidth() - 1));
                itemPositionY = map.getRand(0, (map.getHeight() - 1));
                control=map.getcell(itemPositionX, itemPositionY);
                std::cout << "# control \t" ;
                if ( control== TileType::floor) {//fixme
                    positionFound = true;



                    if (!(bosses.empty())) {
                        if (std::is_same<std::vector<Teleport *>, T>::value) {
                            itemPositionX=bosses[i]->getposX();
                            itemPositionY=bosses[i]->getposY();
                            i++;
                        } else{
                            for (auto gb: bosses) {
                           if (std::is_same<std::vector<Boss *>, T>::value) {
                                    if (l2Distance(*gb, itemPositionX, itemPositionY) <100)
                                        positionFound = false;
                                } else {
                                    if (gb->getposY() == itemPositionY && gb->getposX() == itemPositionX)
                                        positionFound = false;
                                }
                        }
                    }}


                    if (!(items.empty())) {
                        for (auto gi: items) {
                            if(std::is_same<std::vector<Item *>,T>::value){
                                if (l2Distance(*gi,itemPositionX,itemPositionY)<15)
                                    positionFound = false;
                            }else{
                                if (gi->getposY() == itemPositionY && gi->getposX() == itemPositionX)
                                positionFound = false;
                            }
                        }
                    }

                    if (!(enemies.empty())) {
                        for (auto ge: enemies) {
                            if(std::is_same<std::vector<Obstacle *>,T>::value){
                                if (l2Distance(*ge,itemPositionX,itemPositionY)<15)
                                    positionFound = false;
                            }else{
                                if (ge->getposY() == itemPositionY && ge->getposX() == itemPositionX)
                                positionFound = false;
                            }
                        }
                    }

                    if (!(safezones.empty())) {
                        for (auto gs: safezones) {
                            if(std::is_same<std::vector<Object *>,T>::value){
                                if (l2Distance(*gs,itemPositionX,itemPositionY)<50)
                                    positionFound = false;
                            }else{
                                if (gs->getposY() == itemPositionY && gs->getposX() == itemPositionX)
                                positionFound = false;
                            }
                        }
                    }

                }

                if(positionFound)
                    break;
            }gc->setposX(itemPositionX);
            gc->setposY(itemPositionY);


        }
    }

    std::vector<Obstacle*> enemies;
    std::vector<Item*> items;
    std::vector<Object*> safezones;
    std::vector<Teleport*> teleports;
    std::vector<Boss*> bosses;
private:
    int monsterNumber=0;
    int objectNumber=0;
    int safezoneNumber=0;
    int bossNumber=0;

};


#endif //MAIN_SPAWNER_H
