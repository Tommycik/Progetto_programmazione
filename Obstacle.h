//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_OBSTACLE_H
#define MAIN_OBSTACLE_H
#include "Entity.h"

enum class enemy{
    blocked=0
};

class Obstacle: public Entity {

public:

    Obstacle(int hp, int movements, int posX, int posY, bool fixed);

    void behaviour() override;
    void tracking() override;
    void move(int x, int y) override;
    void fight() override;
    bool isFixed() const;
    bool isActivated() const;
    void setFixed(bool fixed);
    void setType(enemy type);
    int getObstacleType() const;
    void setObstacleType(int obstacleType);
    void setActivated(bool activated);
    enemy getType() const;

protected:

    bool activated=false;
    bool fixed=true;
    enemy type=enemy::blocked;

};


#endif //MAIN_OBSTACLE_H
