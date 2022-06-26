//
// Created by tommy on 16/06/2022.
//

#include "Entity.h"
#include "Object.h"

Entity::Entity(int hp, int movements, int posX, int posY):Object(movements,posX,posY) {
    this->hp=hp;
}

int Entity::getHp() const {
    return hp;
}

void Entity::setHp(int hp) {
    Entity::hp = hp;
}


void Entity::run(int x,int y) {
    if (x > movements ||x<-movements)
        x = movements;
    if (y > movements||y<-movements)
        y = movements;
    posX += 2*x;
    posY += 2*y;
}
