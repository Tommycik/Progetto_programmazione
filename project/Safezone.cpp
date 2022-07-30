//
// Created by tommy on 08/07/2022.
//

#include "Safezone.h"

Safezone::Safezone(int posX, int posY,int moving) {
    this->movements=moving;
    this->posX=posX;
    this->posY=posY;
    this->tileNumber =42*3;

}

bool Safezone::isUsed() const {
    return used;
}

void Safezone::setUsed(bool used) {
    Safezone::used = used;
}

