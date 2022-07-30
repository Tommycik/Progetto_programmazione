//
// Created by tommy on 30/07/2022.
//

#ifndef MAIN_STATICDANGER_H
#define MAIN_STATICDANGER_H
#include "Obstacle.h"

class StaticDanger :public Obstacle{
public:

    StaticDanger(int hp, int movements, int posX, int posY, bool fixed, int mapNumber);

private:

};


#endif //MAIN_STATICDANGER_H
