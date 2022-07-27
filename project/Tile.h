//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_TILE_H
#define MAIN_TILE_H

enum class TileType{
    Unused=0,wall=1,floor=2,corridor=3,damagedfloor=4,destructible=5,door=6,pebble=7
};//

class Tile{

public:

    bool isDestructble() const;
    void unlockPassage(bool unlock);

    TileType getType() const;
    void setType( TileType tile);
    bool isPassable() const;
    void setPassable(bool passable);
    bool isSpawnPlace() const;
    void setSpawnPlace(bool spawnPlace);

private:

    bool passable=true;
    bool spawnPlace=true;
    bool destructible=false;
    TileType type=TileType::Unused;
};


#endif //MAIN_TILE_H
