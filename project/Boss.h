//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_BOSS_H
#define MAIN_BOSS_H
#include "Entity.h"

class Boss:public virtual Entity {

public:

    Boss(int hp, int movements, int posX, int posY, int statIncrease);

   void tracking() override;
    void behaviour() override;
    void fight() override;
    void move(int x, int y) override;
    void run(int x, int y) override;
    int getStatIncrease() const;
    void setStatIncrease(int statIncrease);
    int getType() const;

protected:

   //todo implementare nel costruttore un dice che scelga quale boss spawnare
   int statIncrease;
   int type=0;
    //todo implementarlo nei salvataggi
};



#endif //MAIN_BOSS_H
