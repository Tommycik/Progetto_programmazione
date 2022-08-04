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

void Obstacle::run(int x, int y) {

}

bool Obstacle::isKillable() const {
    return killable;
}

int Obstacle::getType() const {
    return type;
}

Obstacle::~Obstacle() {

}

