//
// Created by tommy on 16/06/2022.
//

#include "Obstacle.h"

bool Obstacle::isFixed() const {
    return fixed;
}

void Obstacle::setFixed(bool fixed) {
    Obstacle::fixed = fixed;
}

void Obstacle::run(float x, float y) {}

Obstacle::~Obstacle() {}

