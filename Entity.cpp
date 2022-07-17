//
// Created by tommy on 16/06/2022.
//

#include "Entity.h"




int Entity::getHp() const {
    return hp;
}

void Entity::setHp(int hp) {
   this->hp = hp;
}


void Entity::run(int x,int y) {
    if (x > movements ||x<-movements)
        x = movements;
    if (y > movements||y<-movements)
        y = movements;
    posX += 2*x;
    posY += 2*y;
}


void Entity::fight() {

}

void Entity::receiveDamage(int damage) {
this->hp-=damage;
}
