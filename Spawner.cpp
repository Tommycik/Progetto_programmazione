//
// Created by tommy on 16/06/2022.
//

#include "Spawner.h"

void Spawner::spawn(int startX, int startY, const int numObstacle, const int numObject, const int numSafezone,
                    const int numBoss, const Dungeonarea &map) {
  Spawner::enemies.reserve(numObstacle);
    Spawner::safezones.reserve(numSafezone);
    Spawner::items.reserve(numObject);
    Spawner::bosses.reserve(numBoss);
    Spawner::teleports.reserve(numBoss);

}
