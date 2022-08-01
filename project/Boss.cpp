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

void Boss::tracking() {

}

void Boss::behaviour() {

}

void Boss::move(int x, int y) {

}

void Boss::fight() {

}

void Boss::run(int x, int y) {

}

int Boss::getType() const {
    return type;
}


