//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_OBSTACLE_H
#define MAIN_OBSTACLE_H
#include "Entity.h"

class Obstacle: public Entity {

public:
    Obstacle();
    explicit Obstacle(int hp, int movements, int posX, int posY, bool fixed);

    bool isFixed() const;

    bool isActivated() const;

    void setFixed(bool fixed);

    void setActivated(bool activated);

protected:
    bool activated=false;
    bool fixed=true;
};


#endif //MAIN_OBSTACLE_H
