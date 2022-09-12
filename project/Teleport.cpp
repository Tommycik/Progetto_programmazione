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

Teleport::Teleport(int posX, int posY) {
    this->movements = 0;
    this->posX = posX;
    this->posY = posY;
}

void Teleport::teleportation(Mario &hero) {
    hero.setposX(this->getposX());
    hero.setposY(this->getposY());
}
