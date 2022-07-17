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
}

Item::Item( int posX, int posY, int effect,int movements){
   this->taken=false;
   this->effect=effect;
   this->movements=movements;
   this->posX=posX;
   this->posY=posY;
}


