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

void Entity::receiveDamage(int damage) {
this->hp-=damage;
}
