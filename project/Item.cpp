//
// Created by tommy on 16/06/2022.
//

#include "Item.h"

bool Item::isTaken() const {
    return taken;
}

void Item::setTaken(bool taken) {
    Item::taken = taken;
}

int Item::getEffect() const {
    return effect;
}

void Item::setEffect(int effect) {
    Item::effect = effect;
    tileNumber = 12;

    if (this->effect == 2) {
        tileNumber = 3;
    } else if (this->effect == 3) {
        tileNumber = 7;
    }

}

Item::Item(int posX, int posY, int effect) {
    this->taken = false;
    this->effect = effect;
    this->movements = 0;
    this->posX = posX;
    this->posY = posY;
    tileNumber = 12;

    if (this->effect == 2) {
        tileNumber = 3;
    } else if (this->effect == 3) {
        tileNumber = 7;
    }

}


