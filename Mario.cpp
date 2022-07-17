//
// Created by tommy on 16/06/2022.
//

#include "Mario.h"
#include "Entity.h"
#include "Object.h"
Mario::Mario(int hp, int movements, int posX, int posY, int stamina, int potioNum,int bossKill):stamina(stamina),
maxHp(hp),maxStam(stamina),potionNum(potioNum){
    this->hp=hp;
    this->movements=movements;
    this->posX=posX;
    this->posY=posY;
    this->bossKilled=bossKill;
}

float Mario::getStamina() const {
    return stamina;
}

void Mario::stamUse(int stamina) {
    Mario::stamina -= stamina;
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
    Mario::potionNum += potionNum;
}

void Mario::recoverStam(float stamina) {
    if(Mario::stamina<=Mario::maxStam-stamina)
    Mario::stamina += stamina;
}

bool Mario::recoverHp(int potionUsed) {


    if(potionUsed!=0){
        if(Mario::hp<Mario::maxHp){
            if(Mario::hp<=Mario::maxHp-Mario::maxHp/5){
                Mario::hp+=(Mario::maxHp/5);
            }else{
                Mario::hp=Mario::maxHp;
            }

            Mario::potionNum-=potionUsed;}

    }else{
         Mario::hp=Mario::getMaxHp();}
    return true;
}

void Mario::setMaxHp(int maxHp) {
    Mario::maxHp += maxHp;
}

void Mario::setMaxStam(int maxStam) {
    Mario::maxStam += maxStam;
}

void Mario::setStamina(float stamina) {
    Mario::stamina = stamina;
}

void Mario::potionNumSave(int potionNum) {
Mario::potionNum=potionNum;
}

void Mario::maxStamSave(int maxStam) {
Mario::maxStam=maxStam;
}

void Mario::maxHpSave(int maxHp) {
Mario::maxHp=maxHp;
}

int Mario::getBossKilled() const {
    return bossKilled;
}

void Mario::setBossKilled(int bossKilled) {
    Mario::bossKilled = bossKilled;
}




