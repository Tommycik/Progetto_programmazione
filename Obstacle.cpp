//
// Created by tommy on 16/06/2022.
//

#include "Obstacle.h"

Obstacle::Obstacle(int hp, int movements, int posX, int posY,bool fixed) : Entity(hp,movements,posX, posY){
    this->activated=false;
    this->fixed=fixed;
}

bool Obstacle::isFixed() const {
    return fixed;
}

bool Obstacle::isActivated() const {
    return activated;
}

void Obstacle::setActivated(bool activated) {
    Obstacle::activated = activated;
}

void Obstacle::setFixed(bool fixed) {
    Obstacle::fixed = fixed;
}
