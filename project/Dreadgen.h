//
// Created by tommy on 08/09/2022.
//

#ifndef MAIN_DREADGEN_H
#define MAIN_DREADGEN_H
#include "Boss.h"
#include "Fireball.h"
#include "CrystalWall.h"

class Dreadgen: public Boss {

public:

    Dreadgen(int posX,int posY,int dungeonType);

    void tracking(Entity &target) override;
    void behaviour(Entity &target) override;
    void move(float x, float y) override;
    std::unique_ptr<Skills> skillUse() override;

};


#endif //MAIN_DREADGEN_H
