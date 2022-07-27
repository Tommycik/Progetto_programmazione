//
// Created by tommy on 16/06/2022.
//

#include "Skills.h"

void Skills::tracking() {}

void Skills::behaviour() {

}

void Skills::move(int x, int y) {

}

bool Skills::isOstile() const {
    return ostile;
}

bool Skills::isOutOfRange(int posX, int posY, int initialX, int initialY) {

    if (abs(posX - startX) +(abs(posY - startY) == this->range))
        return true;

    return false;
}

skill Skills::getType() const {
    return type;
}

void Skills::setType(skill type) {
    Skills::type = type;
}

void Skills::run(int x, int y) {

}
