//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_OBSTACLE_H
#define MAIN_OBSTACLE_H
#include "Entity.h"

class Obstacle: public Entity {
protected:
public:
    Obstacle(int hp, int movements, int posX, int posY, const std::string &name, int fixed);

protected:
    bool activated;
    int fixed;
};


#endif //MAIN_OBSTACLE_H
