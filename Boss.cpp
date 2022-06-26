//
// Created by tommy on 16/06/2022.
//

#include "Boss.h"

Boss::Boss(int hp, int movements, int posX, int posY, int statIncrease) : Entity(hp, movements,posX, posY)
                                                                                                    {
    this->statIncrease=statIncrease;
}

int Boss::getStatIncrease() const {
    return statIncrease;
}

void Boss::setStatIncrease(int statIncrease) {
    Boss::statIncrease = statIncrease;
}
