//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_TILE_H
#define MAIN_TILE_H

enum class TileType{
     Unused=0,wall=1,floor=2,corridor=3,damagedfloor,destructible,door=6,pebble

};//
class Tile{
public:
void setX(int posX) {
    Tile::x=posX;
}

int getX() const{
    return x;
}

void setY(int posY) {
        Tile::y=posY;
}

int getY() const{
    return y;
}

    TileType getType() const  {
    return type;
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
    int x;
    int y;
};


#endif //MAIN_TILE_H
