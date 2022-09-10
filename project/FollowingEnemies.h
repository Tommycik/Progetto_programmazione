//
// Created by tommy on 30/07/2022.
//

#ifndef MAIN_FOLLOWINGENEMIES_H
#define MAIN_FOLLOWINGENEMIES_H
#include "Obstacle.h"

class FollowingEnemies: public Obstacle{

public:

    FollowingEnemies(int posX,int posY,int dungeonType);

     void behaviour(Entity &target) override;
     void tracking(Entity &target) override;
     void move(float x, float y) override;

private:

};


#endif //MAIN_FOLLOWINGENEMIES_H
