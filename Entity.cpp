//
// Created by tommy on 16/06/2022.
//

#include "Entity.h"
#include "Object.h"
int Entity::getHp() const {
    return hp;
}

void Entity::setHp(int hp) {
    Entity::hp = hp;
}

Entity::Entity(int hp, int movements, int posX, int posY, std::string name):hp(hp),Object(movements,posX,posY,name) {
}

