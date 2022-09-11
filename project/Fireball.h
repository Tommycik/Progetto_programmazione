//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_FIREBALL_H
#define MAIN_FIREBALL_H

#include "Skills.h"
#include<memory.h>

class Fireball : public Skills {
public:

    Fireball(int posX, int posY, int bossKilled);

    void tracking(Entity &target) override;

    void behaviour(Entity &target) override;

    void move(float x, float y) override;
};

#endif //MAIN_FIREBALL_H
