//
// Created by tommy on 30/07/2022.
//

#include "FollowingEnemies.h"

void FollowingEnemies::behaviour(Entity &target) {
    if(l2Distance(*this,target.getposX(),target.getposY())<=15){
        this->activated=true;
    }else{
        this->activated=false;
    }
    if(activated){
        directX=0;
        directY=0;
        tracking(target);
    }
}

void FollowingEnemies::tracking(Entity &target) {
    float xDistance=0;
    float yDistance=0;
    xDistance=this->posX-target.getposX();
    if(xDistance<0.00)
        xDistance*=-1;
    yDistance=this->posY-target.getposY();
    if(yDistance<0.00)
        yDistance*=-1;

    if(xDistance>yDistance){

        if((this->posX-target.getposX())>0){
            directX=-movements;
        }else if((this->posX-target.getposX())<0){
            directX=movements;
        }

    }else if(xDistance<yDistance){

        if((this->posY-target.getposY())>0){
            directY=-movements;
        }else if((this->posY-target.getposY())<0){
            directY=movements;
        }

    }else if((xDistance==yDistance)){

        if((this->posX-target.getposX())>0){
            directX=-movements;
        }else if((this->posX-target.getposX())<0){
            directX=movements;
        }
        if((this->posY-target.getposY())>0){
            directY=-movements;
        }else if((this->posY-target.getposY())<0){
            directY=movements;
        }
    }
}

void FollowingEnemies::move(float x, float y) {
    /*if (x > movements ||x<-movements)
        //x = movements;
    if (y > movements||y<-movements)*/
       // y = movements;
    posX +=x;//movements*
    posY +=y;
}

FollowingEnemies::FollowingEnemies(int posX, int posY, int dungeonType){

    this->activated=false;
    this->fixed=false;
    this->hp=10+10*dungeonType;
    int n=0;
    int i=0;
    int random=1;
    n = 5 - 1 + 1;
    i = rand() % n;
    if (i < 0)
        i = -i;

    random=1 + i;
    if(random==1){
        this->movements=1;
    }else{
        this->movements=0.5;
    }
/*if(movements==0)
    movements=0.5;*/
    this->posX=posX;
    this->posY=posY;
    this->tileNumber=20;
    this->killable=true;
    this->type=2;
    n = 3 - 1 + 1;
    i = rand() % n;
    if (i < 0)
        i = -i;
    this->hp=1;
    random=1 + i;
    if(random==1)
        this->textureFile="assets/potions.png";
    if(random==2)
        this->textureFile="assets/armours.png";
    if(random==3)
        this->textureFile="assets/books.png";



}

