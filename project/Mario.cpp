//
// Created by tommy on 16/06/2022.
//

#include "Mario.h"

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

void Mario::run(int x, int y) {
    float runSpeed=2;
    if (x > movements ||x<-movements)
        x = movements;
    if (y > movements||y<-movements)
        y = movements;
    posX += runSpeed*x;
    if(x!=0)
    distanceWalked+=runSpeed;
    posY += runSpeed*y;
    if(y!=0)
    distanceWalked+=runSpeed*y;
}

void Mario::move(int x, int y) {
    float speed=1;
    if (x > movements ||x<-movements)
        x = movements;
    if (y > movements||y<-movements)
        y = movements;
    posX += speed*x;
    if(x!=0)
    distanceWalked+=speed;
    posY += speed*y;
    if(y!=0)
    distanceWalked+=speed;
}

void Mario::behaviour() {}

void Mario::tracking() {}

void Mario::fight() {

}

float Mario::getGameTime() const {
    return gameTime;
}

void Mario::setGameTime(float gameTime) {
    Mario::gameTime = gameTime;
}

int Mario::getTeleported() const {
    return teleported;
}

void Mario::setTeleported(int teleported) {
    Mario::teleported = teleported;
}

int Mario::getPotionTaken() const {
    return potionTaken;
}

void Mario::setPotionTaken(int potionTaken) {
    Mario::potionTaken = potionTaken;
}

float Mario::getDistanceWalked() const {
    return distanceWalked;
}

void Mario::setDistanceWalked(float distanceWalked) {
    Mario::distanceWalked = distanceWalked;
}

int Mario::getSafezoneUsed() const {
    return safezoneUsed;
}

void Mario::setSafezoneUsed(int safezoneUsed) {
    Mario::safezoneUsed = safezoneUsed;
}

int Mario::getDeaths() const {
    return deaths;
}

void Mario::setDeaths(int deaths) {
    Mario::deaths = deaths;
}



