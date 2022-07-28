//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_MARIO_H
#define MAIN_MARIO_H
#include "Entity.h"
#include "Subject.h"
class Mario :public virtual Entity,public Subject {

public:

    Mario(int hp, int movements, int posX, int posY, int stamina,int potioNum,int bossKill=0 );

    void behaviour() override;
    void tracking() override;
    void fight() override;
    void move(int x, int y) override;
    void run(int x, int y) override;
    float getStamina() const;
    void stamUse(int stamina);
    int getMaxHp() const;
    void setMaxHp(int maxHp);
    void setMaxStam(int maxStam);
    int getMaxStam() const;
    int getPotionNum() const;
    void potionNumSave(int potionNum);
    void maxStamSave(int maxStam);
    void maxHpSave(int maxHp);
    void setStamina(float stamina);
    int getBossKilled() const;
    void setBossKilled(int bossKilled);
    void setPotionNum(int potionNum);
    void recoverStam(float stamina);
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


private:

    float stamina;
    int maxHp;
    int maxStam;
    int potionNum;
    int bossKilled=0;//done
    float gameTime=0;//done
    int teleported=0;//done
    int potionTaken=0;//done
    float distanceWalked=0;//done
    int safezoneUsed=0;//done
    int deaths=0;//done

};


#endif //MAIN_MARIO_H
