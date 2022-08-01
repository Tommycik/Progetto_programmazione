//
// Created by tommy on 16/06/2022.
//

#include "Obstacle.h"

Obstacle::Obstacle(int hp, int movements, int posX, int posY,bool fixed){
    
    this->activated=false;
    this->fixed=fixed;
    this->hp=hp;
    this->movements=movements;
    this->posX=posX;
    this->posY=posY;
}

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

void Obstacle::tracking() {

}

void Obstacle::behaviour() {

}

void Obstacle::move(int x, int y) {

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
