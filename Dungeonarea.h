//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_DUNGEONAREA_H
#define MAIN_DUNGEONAREA_H
#include <iostream>
#include "Tile.h"
#include "Template.h"

class Dungeonarea {//todo aggiungere metodo distanza con il template
public:

    explicit Dungeonarea(int maxlength,int maxheigth,int minRoomWidth,int minRoomHeight,int mapType,int chanceRoom,int parts,int xMin,int yMin);

    ~Dungeonarea();
    bool isLegalCell(int x, int y, Dungeonarea &map) ;


    bool createDungeon(int xLength,int yLength ,int inobj );//todo inserire if e clo per creare stanza boss e spawnarvi boss, inserire modo per creare stanze segrete
    bool makeCorridor(int x,int y , int length , int direction);
    bool makeRoom(int x, int y, int xlength,int ylenghth,int direction);
    int getWidth() const;
    void setWidth(int xSixe);
    int getHeight() const;
    void setHeight(int ySize);
    int getRand(int min, int max);
    Tile getcell(int x,int y) ;

private:
    int width;
    int height;
    int xMin;
    int yMin;
    int xMax;
    int yMax;
    int parts;
    int minRoomWidth;
    int minRoomHeight;
    int dungeonType;
    int chanceRoom;
    int chanceCorridor;
    long oldseed;
    std::string name;
    std::string save;
    Tile* tiles;
};


#endif //MAIN_DUNGEONAREA_H
