//
// Created by tommy on 16/06/2022.
//

#include "Boss.h"

Boss::Boss(int hp, int movements, int posX, int posY, int statIncrease){
    this->hp=hp;
    this->movements=movements;
    this->posX=posX;
    this->posY=posY;
    this->statIncrease=statIncrease;
}

int Boss::getStatIncrease()const{
    return statIncrease;
}

void Boss::setStatIncrease(int statIncrease) {
    Boss::statIncrease = statIncrease;
}

void Boss::tracking(Entity &target) {

}

void Boss::behaviour(Entity &target) {

}

void Boss::move(float x, float y) {

}

void Boss::fight() {

}

void Boss::run(float x, float y) {

}



