//
// Created by tommy on 30/07/2022.
//

#include "FollowingEnemies.h"

void FollowingEnemies::behaviour() {

}

void FollowingEnemies::tracking() {

}

void FollowingEnemies::move(int x, int y) {

}

FollowingEnemies::FollowingEnemies(int hp, int movements, int posX, int posY, bool fixed, int dungeonType){

    this->activated=false;
    this->fixed=fixed;
    this->hp=hp;
    this->movements=movements;
    this->posX=posX;
    this->posY=posY;
    this->tileNumber=20;
    this->killable=true;
    this->type=2;
    this->textureFile="assets/potions.png";
}
