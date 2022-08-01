//
// Created by tommy on 30/07/2022.
//

#include "FollowingEnemies.h"

void FollowingEnemies::behaviour() {
    Obstacle::behaviour();
}

void FollowingEnemies::tracking() {
    Obstacle::tracking();
}

void FollowingEnemies::move(int x, int y) {
    Obstacle::move(x, y);
}

FollowingEnemies::FollowingEnemies(int hp, int movements, int posX, int posY, bool fixed, int dungeonType) : Obstacle(hp, movements,
                                                                                                     posX, posY,
                                                                                                     fixed) {
    this->tileNumber=dungeonType;
    this->killable=true;
    this->type=3;
}
