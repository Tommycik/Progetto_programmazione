//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_TILE_H
#define MAIN_TILE_H

enum class TileType{
     Unused=0,wall,floor,corridor,damagedfloor,destructible,door,pebble

};//
class Tile{
public:


    Tile(){
        this->type=TileType::Unused;
    };

    TileType getType() const  {
    return Tile::type;
}

    void setType( TileType tile){
    Tile::type=tile;
}
    bool isDestructble() const;
    bool isPassable() const;
    void unlockPassage(bool unlock);

private:
    bool destructible;
    bool passable;
    TileType type;
};


#endif //MAIN_TILE_H
