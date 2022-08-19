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

void Tile::setType(TileType tile,int dungeonType){
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
    int random=1;
    int n=0;
    int i=0;
   /* long seed = time(NULL) + oldseed;
    this->oldseed = seed;
    srand(seed);*/

    if(tile== TileType::Unused){
        switch (dungeonType) {
            case 0://forest
                tileNumber=31*17+60;
                break;
            case 1://cave
                tileNumber=31+12;
                break;
            case 2://brick
                tileNumber=31*6+14;
                break;
            case 3://chocolate
                tileNumber=31*22-3;
                break;
            case 4://lava
                tileNumber=31*13+23;
                break;
            case 5://sand
                tileNumber=31*12+13;
                break;
            default:
                tileNumber=31*17+60;
                break;
        }
    }else if(tile== TileType::floor){
        switch (dungeonType) {
            case 0://forest
                tileNumber=31*27-5;
                break;
            case 1://cave
                tileNumber=31+11;
                break;
            case 2://brick
                 n = 10 - 1 + 1;
                 i = rand() % n;
                if (i < 0)
                    i = -i;

                random=1 + i;
                if(random<=9){
                    tileNumber=31*6+6;
                }else{
                    tileNumber=31*6+8;
                }
                break;
            case 3://chocolate
                tileNumber=31*22-8;
                break;
            case 4://lava
                 n = 5 - 1 + 1;
                 i = rand() % n;
                if (i < 0)
                    i = -i;

                random=1 + i;
                if(random<=4){
                    tileNumber=31*14+27;
                }else{
                    tileNumber=31*13+14;}
                break;
            case 5://sand
                tileNumber=31*16+27;
                break;
            default:
                tileNumber=31*27-5;
                break;
        }
    }else if(tile== TileType::wall){
        switch (dungeonType) {
            case 0://forest
                tileNumber=31*17+57;
                break;
            case 1://cave
                tileNumber=31+12;
                break;
            case 2://brick
                tileNumber=31*6+13;
                break;
            case 3://chocolate
                tileNumber=31*22-7;
                break;
            case 4://lava
                tileNumber=31*13+23;
                break;
            case 5://sand
                tileNumber=31*12+12;
                break;
            default:
                tileNumber=31*17+57;
                break;
        }
    }else if(tile== TileType::corridor){
        switch (dungeonType) {
            case 0://forest
                tileNumber=31*17+55;
                break;
            case 1://cave
                tileNumber=31+11;
                break;
            case 2://brick
                tileNumber=31*6+6;
                break;
            case 3://chocolate
                tileNumber=31*22+7;
                break;
            case 4://lava
                //get rand
                n = 5 - 1 + 1;
                i = rand() % n;
                if (i < 0)
                    i = -i;

                random=1 + i;
                if(random<=4){
                    tileNumber=31*14+27;
                }else{
                    tileNumber=31*13+14;}
                break;
            case 5://sand
                tileNumber=31*16+27;
                break;
            default:
                tileNumber=31*17+55;
                break;
        }
    }else if(tile== TileType::door){
        switch (dungeonType) {
            case 0://forest
                tileNumber=31*17+55;
                break;
            case 1://cave
                tileNumber=31+11;
                break;
            case 2://brick
                tileNumber=31*6+6;
                break;
            case 3://chocolate
                tileNumber=31*22+7;
                break;
            case 4://lava
                //get rand
                n = 5 - 1 + 1;
                i = rand() % n;
                if (i < 0)
                    i = -i;

                random=1 + i;
                if(random<=4){
                    tileNumber=31*14+27;
                }else{
                    tileNumber=31*13+14;
                }
                break;
            case 5://sand
                tileNumber=31*16+27;
                break;
            default:
                tileNumber=31*17+55;
                break;
        }
    }
}

TileType Tile::getType() const {
    return type;
}

int Tile::getTileNumber() const {
    return tileNumber;
}

void Tile::setTileNumber(int tileNumber) {
    Tile::tileNumber = tileNumber;
}


