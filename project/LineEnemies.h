//
// Created by tommy on 30/07/2022.
//

#ifndef MAIN_LINEENEMIES_H
#define MAIN_LINEENEMIES_H
#include "Obstacle.h"

class LineEnemies: public Obstacle{

public:

    void behaviour() override;
    void move(int x, int y) override;

};


#endif //MAIN_LINEENEMIES_H
