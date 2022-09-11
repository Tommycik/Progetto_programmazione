//
// Created by tommy on 30/07/2022.
//

#ifndef MAIN_STATICDANGER_H
#define MAIN_STATICDANGER_H

#include "Obstacle.h"

class StaticDanger : public Obstacle {

public:

    StaticDanger(int posX, int posY, int dungeonType);

    void behaviour(Entity &target) override;

    void tracking(Entity &target) override;

    void move(float x, float y) override;

private:
};


#endif //MAIN_STATICDANGER_H
