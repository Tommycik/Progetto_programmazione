//
// Created by tommy on 16/06/2022.
//

#include "Skills.h"

void Skills::tracking(Entity &target) {}

void Skills::behaviour(Entity &target) {}

void Skills::move(float x, float y) {}

bool Skills::isOstile() const {
    return ostile;
}

bool Skills::isOutOfRange(int posX, int posY, int initialX, int initialY) {
    if (abs(posX - startX) + (abs(posY - startY) >= this->range))
        return true;
    return false;
}

void Skills::run(float x, float y) {}

Entity *Skills::getTarget() const {
    return target;
}

bool Skills::isTargetLost() const {
    return targetLost;
}

float Skills::getRadius() const {
    return radius;
}

bool Skills::isTargetFound() const {
    return targetFound;
}

void Skills::setTargetFound(bool targetFound) {
    Skills::targetFound = targetFound;
}

void Skills::setOstile(bool ostile) {
    Skills::ostile = ostile;
}

Entity *Skills::getUser() const {
    return user;
}

void Skills::setUser(Entity *user) {
    Skills::user = user;
}




