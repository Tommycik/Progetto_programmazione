//
// Created by tommy on 22/06/2022.
//

#include "Teleport.h"

bool Teleport::isActivated() const {
    return activated;
}

void Teleport::setActivated(bool activated) {
    Teleport::activated = activated;
}

Teleport::Teleport(int posX, int posY) : Object(movements=0, posX,posY){
    this->activated= true;}

void teleportation(Mario &hero,int finalX,int finalY){
    hero.setposX(finalX);
    hero.setposY(finalY);
}
