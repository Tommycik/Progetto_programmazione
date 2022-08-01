//
// Created by tommy on 30/07/2022.
//

#include "LineEnemies.h"

void LineEnemies::behaviour() {
    if(!activated){
//if(l2Distance())
    }
}

void LineEnemies::move(int x, int y) {
    float speed=1;
    if (x > movements ||x<-movements)
        x = movements;
    if (y > movements||y<-movements)
        y = movements;

    posX += speed*x;
    posY += speed*y;

}

LineEnemies::LineEnemies(int hp, int movements, int posX, int posY, bool fixed,int dungeonType) : Obstacle(hp, movements, posX, posY,
                                                                                           fixed) {

    this->tileNumber=dungeonType;
    this->killable=false;
    this->type=2;
}
