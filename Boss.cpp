//
// Created by tommy on 16/06/2022.
//

#include "Boss.h"

Boss::Boss(int hp, int movements, int posX, int posY, const std::string &name, int statIncrease) : Entity(hp, movements,
                                                                                                          posX, posY,
                                                                                                          name),
                                                                                                   statIncrease(
                                                                                                           statIncrease) {}
