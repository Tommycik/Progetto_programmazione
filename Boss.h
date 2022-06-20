//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_BOSS_H
#define MAIN_BOSS_H
#include "Entity.h"

class Boss:public Entity {
public:
    Boss(int hp, int movements, int posX, int posY, const std::string &name, int statIncrease);


protected:
    int statIncrease;

};



#endif //MAIN_BOSS_H
