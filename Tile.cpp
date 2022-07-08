//
// Created by tommy on 16/06/2022.
//

#include "Tile.h"
bool Tile::isDestructble() const {
    return destructible;
}
bool Tile::isPassable() const{
    return passable;
}
void Tile::unlockPassage(bool unlock){
    passable=unlock;
}