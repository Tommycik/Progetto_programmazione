//
// Created by tommy on 30/07/2022.
//

#ifndef MAIN_FOLLOWINGENEMIES_H
#define MAIN_FOLLOWINGENEMIES_H
#include "Obstacle.h"

class FollowingEnemies: public Obstacle{

public:

    void behaviour() override;
    void tracking() override;
    void move(int x, int y) override;

};


#endif //MAIN_FOLLOWINGENEMIES_H
