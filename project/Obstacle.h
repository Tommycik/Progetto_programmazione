//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_OBSTACLE_H
#define MAIN_OBSTACLE_H
#include "Entity.h"

class Obstacle: public virtual Entity {

public:

    Obstacle(int hp, int movements, int posX, int posY, bool fixed);

    void behaviour() override;
    void tracking() override;
    void move(int x, int y) override;
    void fight() override;
    bool isFixed() const;
    bool isActivated() const;
    void setFixed(bool fixed);
    int getObstacleType() const;
    void setObstacleType(int obstacleType);
    void setActivated(bool activated);
    void run(int x, int y) override;

protected:

    bool activated=false;
    bool fixed=true;

};


#endif //MAIN_OBSTACLE_H
