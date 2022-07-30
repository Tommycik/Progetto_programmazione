//
// Created by tommy on 30/07/2022.
//

#include "StaticDanger.h"


StaticDanger::StaticDanger(int hp, int movements, int posX, int posY, bool fixed, int mapNumber)
        : Obstacle(hp, movements, posX, posY, fixed){
    this->tileNumber=mapNumber;

}
