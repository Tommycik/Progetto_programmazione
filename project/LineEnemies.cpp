//
// Created by tommy on 30/07/2022.
//

#include "LineEnemies.h"

void LineEnemies::behaviour(Entity &target) {
    /*if(!activated){
//if(l2Distance())
    }*/
}

void LineEnemies::move(float x, float y) {
    float speed=1;
    if (x > movements ||x<-movements)
        x = movements;
    if (y > movements||y<-movements)
        y = movements;

    posX += speed*x;
    posY += speed*y;

}

LineEnemies::LineEnemies(int hp, int movements, int posX, int posY, bool fixed,int dungeonType){

    this->activated=false;
    this->fixed=fixed;
    this->hp=hp;
    this->movements=movements;
    this->posX=posX;
    this->posY=posY;
    this->tileNumber=15;
    this->killable=false;
    this->type=2;
    this->textureFile="assets/TileSet.png";
}

void LineEnemies::tracking(Entity &target) {

}
