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

Teleport::Teleport(int posX, int posY) : Object(movements=0, posX,posY, name="teleport")
                                                                                                 {
    this->activated= true;
                                                                                                 }
