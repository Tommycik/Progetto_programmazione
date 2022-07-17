//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_MARIO_H
#define MAIN_MARIO_H
#include "Entity.h"

class Mario :public Entity{

public:

    Mario(int hp, int movements, int posX, int posY, int stamina,int potioNum,int bossKill=0 );

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

private:

    float stamina;
    int maxHp;
    int maxStam;
    int potionNum;
    int bossKilled=0;
};


#endif //MAIN_MARIO_H
