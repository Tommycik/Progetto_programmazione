//
// Created by tommy on 16/06/2022.
//

#include "Tile.h"
bool Tile::isDestructble() const {
    return destructible;
}


void Tile::unlockPassage(bool unlock){
    Tile::type=TileType::corridor;
}