//
// Created by tommy on 16/06/2022.
//

#include "Obstacle.h"

Obstacle::Obstacle(int hp, int movements, int posX, int posY, const std::string &name,int fixed) : Entity(hp,
                                                                                                           movements,
                                                                                                           posX, posY,
                                                                                                           name),
                                                                                                    fixed(fixed) {}
