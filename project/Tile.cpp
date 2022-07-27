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

bool Tile::isPassable() const {
    return passable;
}

void Tile::setPassable(bool passable) {
    Tile::passable = passable;
}

bool Tile::isSpawnPlace() const {
    return spawnPlace;
}

void Tile::setSpawnPlace(bool spawnPlace) {
    Tile::spawnPlace = spawnPlace;
}

void Tile::setType(TileType tile){
    this->type=tile;
    if(this->type==TileType::Unused||this->type==TileType::wall ){
        this->passable=false;
    }else{
        this->passable=true;
    }
    if(this->type==TileType::door||this->type==TileType::damagedfloor||this->type==TileType::corridor){
        this->spawnPlace=false;
    }else{
        this->spawnPlace=true;
    }
}

TileType Tile::getType() const {
    return type;
}


