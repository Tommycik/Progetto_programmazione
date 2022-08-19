//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_BOSS_H
#define MAIN_BOSS_H
#include "Entity.h"

class Boss:public  Entity {

public:

    Boss(int hp, int movements, int posX, int posY, int statIncrease);

   void tracking(Entity &target) override;
    void behaviour(Entity &target) override;
    void fight() override;
    void move(float x, float y) override;
    void run(float x, float y) override;
    int getStatIncrease() const;
    void setStatIncrease(int statIncrease);

protected:

   int statIncrease;

};



#endif //MAIN_BOSS_H
