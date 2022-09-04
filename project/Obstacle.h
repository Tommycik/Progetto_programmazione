//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_OBSTACLE_H
#define MAIN_OBSTACLE_H
#include "Entity.h"



class Obstacle: public Entity {

public:

    virtual ~Obstacle();

    void fight() override;
    bool isFixed() const;
    void setFixed(bool fixed);
    void setObstacleType(int obstacleType);
    void run(float x, float y) override;

protected:

    bool fixed=true;


};


#endif //MAIN_OBSTACLE_H
