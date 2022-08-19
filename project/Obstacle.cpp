//
// Created by tommy on 16/06/2022.
//

#include "Obstacle.h"

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


void Obstacle::fight() {

}

void Obstacle::run(float x, float y) {

}

bool Obstacle::isKillable() const {
    return killable;
}


Obstacle::~Obstacle() {

}

