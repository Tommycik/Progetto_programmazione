//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_MARIO_H
#define MAIN_MARIO_H
#include "Entity.h"
#include "Subject.h"
#include "Fireball.h"
#include "Iceslide.h"
class Mario :public  Entity,public Subject {

public:

    Mario(int hp, int movements, int posX, int posY, int stamina,int potioNum,int bossKill=0 );

    void behaviour(Entity &target) override;
    void tracking(Entity &target) override;
    void fight() override;
    void move(float x, float y) override;
    void run(float x, float y) override;
    float getStamina() const;
    void stamUse(int stamina);
    int getMaxHp() const;
    void setMaxHp(int maxHp);
    void setMaxStam(int maxStam);
    float getMaxStam() const;
    int getPotionNum() const;
    void potionNumSave(int potionNum);
    void maxStamSave(int maxStam);
    void maxHpSave(int maxHp);
    void setStamina(float stamina);
    int getBossKilled() const;
    void setBossKilled(int bossKilled);
    void setPotionNum(int potionNum);
    void recoverStam();
    bool recoverHp(int potionUsed);
    float getGameTime() const;
    void setGameTime(float gameTime);
    int getTeleported() const;
    void setTeleported(int teleported);
    int getPotionTaken() const;
    void setPotionTaken(int potionTaken);
    float getDistanceWalked() const;
    void setDistanceWalked(float distanceWalked);
    int getSafezoneUsed() const;
    void setSafezoneUsed(int safezoneUsed);
    int getDeaths() const;
    void setDeaths(int deaths);
    float getRunningMovement() const;
    std::unique_ptr<Fireball> skillUse();


private:

    float stamina;

    float runningMovement;
    int maxHp=0;
    float maxStam=0;
    int potionNum=0;
    int bossKilled=0;
    float gameTime=0;
    int teleported=0;
    int potionTaken=0;
    float distanceWalked=0;
    int safezoneUsed=0;
    int deaths=0;

};


#endif //MAIN_MARIO_H
