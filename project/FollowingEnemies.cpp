//
// Created by tommy on 30/07/2022.
//

#include "FollowingEnemies.h"

void FollowingEnemies::behaviour(Entity &target) {
    if (l2Distance(*this, target.getposX(), target.getposY()) <= 15) {
        this->activated = true;
    } else {
        this->activated = false;
    }

    if (activated) {
        directX = 0;
        directY = 0;
        tracking(target);
    }

}

void FollowingEnemies::tracking(Entity &target) {
    float xDistance = 0;
    float yDistance = 0;
    xDistance = this->posX - target.getposX();
    if (xDistance < 0.00)
        xDistance *= -1;
    yDistance = this->posY - target.getposY();
    if (yDistance < 0.00)
        yDistance *= -1;

    if (xDistance > yDistance) {

        if ((this->posX - target.getposX()) > 0) {
            directX = -movements;
        } else if ((this->posX - target.getposX()) < 0) {
            directX = movements;
        }

    } else if (xDistance < yDistance) {

        if ((this->posY - target.getposY()) > 0) {
            directY = -movements;
        } else if ((this->posY - target.getposY()) < 0) {
            directY = movements;
        }

    } else if ((xDistance == yDistance)) {

        if ((this->posX - target.getposX()) > 0) {
            directX = -movements;
        } else if ((this->posX - target.getposX()) < 0) {
            directX = movements;
        }

        if ((this->posY - target.getposY()) > 0) {
            directY = -movements;
        } else if ((this->posY - target.getposY()) < 0) {
            directY = movements;
        }

    }
}

void FollowingEnemies::move(float x, float y) {
    posX += x;
    posY += y;
}

FollowingEnemies::FollowingEnemies(int posX, int posY, int dungeonType) {
    this->textureMultiplier = 2;
    this->activated = false;
    this->fixed = false;
    this->hp = 5 + 10 * dungeonType;
    this->contactDamage = 20;
    int n = 0;
    int i = 0;
    int random = 1;
    this->movements = 1;
    this->posX = posX;
    this->posY = posY;
    this->textureFile = "assets/enemies.png";
    this->killable = true;
    this->type = 2;

    n = 20 - 1 + 1;
    i = rand() % n;
    if (i < 0)
        i = -i;
    random = 1 + i;

    if (random == 1) {
        this->tileNumber = 0;
        this->hp = 1 + 15 * dungeonType;
        this->contactDamage = 5 + 10 * dungeonType;
        this->movements = 3;
    }
    if (random == 2) {
        this->tileNumber = 2;
        this->hp = 10 + 15 * dungeonType;
        this->contactDamage = 15 + 10 * dungeonType;
    }
    if (random == 3) {
        this->tileNumber = 11;
        this->hp = 15 + 20 * dungeonType;
        this->contactDamage = 15 + 10 * dungeonType;
    }
    if (random == 4) {
        this->tileNumber = 24;
        this->hp = 10 + 15 * dungeonType;
        this->contactDamage = 10 + 5 * dungeonType;
    }
    if (random == 5) {
        this->tileNumber = 25;
        this->hp = 20 + 20 * dungeonType;
        this->contactDamage = 15 + 10 * dungeonType;
    }
    if (random == 6) {
        this->tileNumber = 26;
        this->hp = 30 + 20 * dungeonType;
        this->contactDamage = 20 + 15 * dungeonType;
    }
    if (random == 7) {
        this->tileNumber = 27;
        this->hp = 10 + 10 * dungeonType;
        this->contactDamage = 30 + 20 * dungeonType;
        this->movements = 0.5;
    }
    if (random == 8) {
        this->tileNumber = 41;
        this->hp = 10 + 10 * dungeonType;
        this->contactDamage = 5 + 10 * dungeonType;
    }
    if (random == 9) {
        this->tileNumber = 46;
        this->hp = 25 + 30 * dungeonType;
        this->contactDamage = 5 + 5 * dungeonType;
        this->movements = 0.5;
    }
    if (random == 10) {
        this->tileNumber = 51;
        this->hp = 10 + 10 * dungeonType;
        this->contactDamage = 10 + 10 * dungeonType;
    }
    if (random == 11) {
        this->tileNumber = 53;
        this->hp = 50 + 40 * dungeonType;
        this->contactDamage = 10 + 10 * dungeonType;
        this->movements = 0.5;
    }
    if (random == 12) {
        this->tileNumber = 33;
        this->hp = 15 + 10 * dungeonType;
        this->contactDamage = 25 + 20 * dungeonType;
    }
    if (random == 13) {
        this->tileNumber = 160;
        this->hp = 30 + 20 * dungeonType;
        this->contactDamage = 15 + 10 * dungeonType;

    }
    if (random == 14) {
        this->tileNumber = 163;
        this->hp = 10 + 15 * dungeonType;
        this->contactDamage = 20 + 20 * dungeonType;
    }
    if (random == 15) {
        this->tileNumber = 272;
        this->hp = 20 + 15 * dungeonType;
        this->contactDamage = 20 + 15 * dungeonType;
    }
    if (random == 16) {
        this->tileNumber = 6;
        this->hp = 45 + 30 * dungeonType;
        this->contactDamage = 25 + 20 * dungeonType;
    }
    if (random == 17) {
        this->tileNumber = 141;
        this->hp = 60 + 45 * dungeonType;
        this->contactDamage = 30 + 15 * dungeonType;
        this->movements = 0.5;
    }
    if (random == 18) {
        this->tileNumber = 169;
        this->hp = 80 + 60 * dungeonType;
        this->contactDamage = 15 + 10 * dungeonType;
        this->movements = 0.5;
    }
    if (random == 19) {
        this->tileNumber = 130;
        this->hp = 60 + 40 * dungeonType;
        this->contactDamage = 25 + 20 * dungeonType;
    }
    if (random == 20) {//killer
        this->tileNumber = 281;
        this->hp = 1;
        this->contactDamage = 300;
        this->movements = 1.5;
    }
}

