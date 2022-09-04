//
// Created by tommy on 16/06/2022.
//

#include "Fireball.h"

void Fireball::tracking(Entity &target) {
    float xDistance=0;
    float yDistance=0;
    xDistance=this->posX-target.getposX();
    if(xDistance<0)
        xDistance*=-1;
    yDistance=this->posY-target.getposY();
    if(yDistance<0)
        yDistance*=-1;

    if(xDistance>yDistance){

        if((this->posX-target.getposX())>0){
            directX=-movements*1;
        }else if((this->posX-target.getposX())<0){
            directX=movements*1;
        }

    }else if(xDistance<yDistance){

        if((this->posY-target.getposY())>0){
            directY=-movements*1;
        }else if((this->posY-target.getposY())<0){
            directY=movements*1;
        }

    }else if((xDistance==yDistance)){

        if((this->posX-target.getposX())>0){
            directX=-movements*1;
        }else if((this->posX-target.getposX())<0){
            directX=movements*1;
        }
        if((this->posY-target.getposY())>0){
            directY=-movements*1;
        }else if((this->posY-target.getposY())<0){
            directY=movements*1;
        }
    }
}

void Fireball::behaviour(Entity &target) {
    directX=0;
    directY=0;
    tracking(target);
}

void Fireball::move(float x, float y) {
    posX +=x;
    posY +=y;
}


Fireball::Fireball( int posX, int posY,int bossKilled) {
    this->textureMultiplier=2;
    damage=15+15*(bossKilled/2);
    startX=posX;
    startY=posY;
    radius=1.5;
    this->posX=posX;
    this->posY=posY;
    movements=0.5;
    this->hp=1;
    this->textureFile="assets/effectsheet.png";
    this->tileNumber=82;
    stamConsumption=10;
    range=15;
    ostile=false;


}
