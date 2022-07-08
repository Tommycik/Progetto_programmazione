//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_MARIO_H
#define MAIN_MARIO_H
#include "Entity.h"
#include "Object.h"


class Mario :public Entity{

public:
    Mario();
    explicit Mario(int hp, int movements, int posX, int posY, int stamina,int potioNum );
    float getStamina() const;

    void stamUse(int stamina);//manca il consumo calcolato

    int getMaxHp() const;

    void setMaxHp(int maxHp);

    void setMaxStam(int maxStam);

    int getMaxStam() const;

    int getPotionNum() const;
void potionNumSave(int potionNum);
    void maxStamSave(int maxStam);
    void maxHpSave(int maxHp);
    void setStamina(float stamina);

    void setPotionNum(int potionNum);

    void recoverStam(float stamina);//ripresa stam nel tempo
    bool recoverHp(int potionUsed);

private:
    float stamina;
    int maxHp;
    int maxStam;
    int potionNum;
};


#endif //MAIN_MARIO_H
