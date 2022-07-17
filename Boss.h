//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_BOSS_H
#define MAIN_BOSS_H
#include "Entity.h"

enum class boss{
first=0
};

class Boss:public Entity {

public:

    Boss(int hp, int movements, int posX, int posY, int statIncrease);

    virtual void tracking() override;
    virtual void behaviour() override;
    virtual void fight() override;
    virtual void move(int x, int y) override;
    boss getType() const;
    void setType(boss type);
    int getStatIncrease() const;
    void setStatIncrease(int statIncrease);

protected:

    int statIncrease;
    boss type=boss::first;//todo implementarlo nei salvataggi
};



#endif //MAIN_BOSS_H
