//
// Created by tommy on 08/09/2022.
//

#ifndef MAIN_CRYSTALWALL_H
#define MAIN_CRYSTALWALL_H

#include "Skills.h"
#include<memory.h>

class CrystalWall : public Skills {
public:

    CrystalWall(int posX, int posY, int damageMultiplier);

    void tracking(Entity &target) override;

    void behaviour(Entity &target) override;

    void move(float x, float y) override;
};

#endif //MAIN_CRYSTALWALL_H
