//
// Created by tommy on 16/06/2022.
//

#include "Entity.h"

float Entity::getHp() const {
    return hp;
}

void Entity::setHp(float hp) {
   this->hp = hp;
}

void Entity::receiveDamage(int damage) {
this->hp-=damage;
if(hp<0)
    this->hp=0;
}

int Entity::getTextureMultiplier() const {
    return textureMultiplier;
}

float Entity::getDirectX() const {
    return directX;
}

float Entity::getDirectY() const {
    return directY;
}

bool Entity::isChecked() const {
    return checked;
}

void Entity::setChecked(bool checked) {
    Entity::checked = checked;
}
float Entity::getTimeSinceDamage() const {
    return timeSinceDamage;
}

void Entity::setTimeSinceDamage(float timeSinceDamage) {
    Entity::timeSinceDamage += timeSinceDamage;
}

int Entity::getType() const {
    return type;
}

int Entity::getSkillUsed() const {
    return skillUsed;
}

bool Entity::isKillable() const {
        return killable;
}

bool Entity::isActivated() const {
    return activated;
}

float Entity::getContactDamage() const {
    return contactDamage;
}

void Entity::setActivated(bool activated) {
    Entity::activated = activated;
}

bool Entity::isTarget() const {
    return target;
}

void Entity::setTarget(bool target) {
    Entity::target = target;
}
