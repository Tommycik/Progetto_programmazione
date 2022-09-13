//
// Created by tommy on 08/09/2022.
//

#include "CrystalWall.h"

void CrystalWall::tracking(Entity &target) {}

void CrystalWall::behaviour(Entity &target) {
    directX = 0;
    directY = 0;
}

void CrystalWall::move(float x, float y) {
    posX += x;
    posY += y;
}

CrystalWall::CrystalWall(int posX, int posY, int damageMultiplier) {
    this->textureMultiplier = 2;
    damage = 15 + 15 * damageMultiplier;
    radius = 1;
    range = 100;
    int random = 1;
    int n = 0;
    int i = 0;
    n = 10 - 1 + 1;

    i = rand() % n;
    if (i < 0)
        i = -i;
    random = -5 + i;
    if (random == 0) {
        random++;
    }
    this->posX = posX + random;

    i = rand() % n;
    if (i < 0)
        i = -i;
    random = -5 + i;
    if (random == 0) {
        random++;
    }
    this->posY = posY + random;

    movements = 0;
    this->hp = 1;
    this->textureFile = "assets/TileSet.png";
    this->tileNumber = 32 * 63 + 64 * 24 + 4;
    ostile = true;
    stamConsumption = 10;
}
