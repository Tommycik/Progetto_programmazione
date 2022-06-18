//
// Created by tommy on 16/06/2022.
//

#include "Mario.h"
#include "Entity.h"
#include "Object.h"
Mario::Mario(int hp, int movements, int posX, int posY, std::string name, int stamina, int potioNum):Entity(hp,movements,posX,posY,name),
stamina(stamina),maxHp(hp),maxStam(stamina),potionNum(potioNum){
}

int Mario::getStamina() const {
    return stamina;
}

void Mario::stamUse(int stamina) {
    Mario::stamina = stamina;
}

int Mario::getMaxHp() const {
    return maxHp;
}

int Mario::getMaxStam() const {
    return maxStam;
}

int Mario::getPotionNum() const {
    return potionNum;
}

void Mario::setPotionNum(int potionNum) {
    Mario::potionNum = potionNum;
}

void Mario::recoverStam(int stamina) {
    Mario::stamina = stamina;
}

bool Mario::recoverHp(int potionUsed) {

    Mario::potionNum-=potionUsed;
    if(potionUsed!=0){
    Mario::hp+=(Mario::maxHp/5);

    }else{
         Mario::hp=Mario::getMaxHp();}
    return true;
}




