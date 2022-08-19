//
// Created by tommy on 30/07/2022.
//

#ifndef MAIN_LINEENEMIES_H
#define MAIN_LINEENEMIES_H
#include "Obstacle.h"

class LineEnemies: public Obstacle{

public:

    LineEnemies(int hp, int movements, int posX, int posY, bool fixed,int dungeonType);

    void behaviour(Entity &target) override;
    void move(float x, float y) override;
    void tracking(Entity &target) override;

private:

    int dirX=0;
    int dirY=0;
};


#endif //MAIN_LINEENEMIES_H
