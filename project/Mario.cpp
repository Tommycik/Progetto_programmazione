//
// Created by tommy on 16/06/2022.
//

#include "Mario.h"

Mario::Mario(int hp, int movements, int posX, int posY, int stamina, int potioNum,int bossKill):potionNum(potioNum){

    this->maxHp=hp;
    this->maxStam=stamina;
    this->stamina=stamina;
    this->hp=hp;
    this->movements=1;
    this->runningMovement=1.25,
    this->posX=posX;
    this->posY=posY;
    this->bossKilled=bossKill;
}

float Mario::getStamina() const {
    return stamina;
}

void Mario::stamUse(float stamina) {
    Mario::stamina -= stamina;
}

float Mario::getMaxHp() const {
    return maxHp;
}

float Mario::getMaxStam() const {
    return maxStam;
}

int Mario::getPotionNum() const {
    return potionNum;
}

void Mario::setPotionNum(int potionNum) {
    Mario::potionNum += potionNum;
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

void Mario::setMaxHp(float maxHp) {
    Mario::maxHp += maxHp;
}

void Mario::setMaxStam(float maxStam) {
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

void Mario::run(float x, float y) {
   if (x > runningMovement ||x<-runningMovement)
        x = runningMovement;
    if (y > runningMovement||y<-runningMovement)
        y = runningMovement;
    posX +=x;
    if(x!=0)
    distanceWalked+=x;
    posY +=y;
    if(y!=0)
    distanceWalked+=y;
}

void Mario::move(float x, float y) {
    //float speed=1;
    if (x > movements ||x<-movements)
        x = movements;
    if (y > movements||y<-movements)
        y = movements;
    posX += x;
    if(x!=0)
    distanceWalked+=x;
    posY += y;
    if(y!=0)
    distanceWalked+=y;
}

void Mario::behaviour(Entity &target) {}

void Mario::tracking(Entity &target) {}

float Mario::getGameTime() const {
    return gameTime;
}

void Mario::setGameTime(double gameTime) {
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
    Mario::deaths += deaths;
}

float Mario::getRunningMovement() const {
    return runningMovement;
}

std::unique_ptr<Skills> Mario::skillUse() {

    auto newSkill = std::make_unique<Fireball>(this->getposX(),this->getposY(),this->bossKilled);
    //auto newSkill = std::make_unique<CrystalWall>(this->getposX()+1, this->getposY(), bossKilled);
    if(this->stamina>=newSkill->getStamConsumption()){
        skillUsed=1;
        this->stamina-=newSkill->getStamConsumption();
    }else{
        skillUsed=0;
        newSkill= nullptr;
    }

    return newSkill;
}

void Mario::statIncrease(int stat) {

    switch(stat){

        case 1:

            this->hp+=hp/4;
            break;

        case 2:

            this->stamina+=stamina/4;
            break;

        default:

            this->hp+=hp/4;
            break;
    }
}





