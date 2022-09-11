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
double Entity::getTimeSinceDamage() const {
    return timeSinceDamage;
}

void Entity::setTimeSinceDamage(double timeDamage) {
    this->timeSinceDamage = timeDamage;
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

bool Entity::isAbilityUsed() const {
    return abilityUsed;
}

void Entity::setAbilityUsed(bool abilityUsed) {
    Entity::abilityUsed = abilityUsed;
}

void Entity::recoverStam() {
    if(this->stamina<=this->maxStam-(this->maxStam/80))
        this->stamina += (this->maxStam/80);
}

float Entity::getInvulnerabilityFrame() const {
    return invulnerabilityFrame;
}

void Entity::setInvulnerabilityFrame(float invulnerabilityFrame) {
    Entity::invulnerabilityFrame = invulnerabilityFrame;
}
