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

Item::Item(int movements, int posX, int posY, const std::string &name, int effect) : Object(movements, posX, posY,
                                                                                            name), effect(effect) {
   Item::taken=false;
}


