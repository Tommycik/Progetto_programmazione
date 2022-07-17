//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_DUNGEONAREA_H
#define MAIN_DUNGEONAREA_H

#include <iostream>
#include "Tile.h"
#include "Template.h"
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include "GameFileException.h"

static std::string TileTypeToTileString(const TileType& tile) {
    switch (tile) {
        case TileType::Unused:
            return "u";
        case TileType::wall:
            return "w";
        case TileType:: floor:
            return "+";
        case TileType::door:
            return ".";
        case TileType::corridor:
            return "#";
        case TileType::damagedfloor:
            return "D";
        case TileType::destructible:
            return "<";
        case TileType::pebble:
            return ">";
        default:
            return "u";
    };
}

static TileType TileStringToTileType(const char& tile) {
    switch (tile) {
        case 'u':
            return TileType::Unused;
        case 'w':
            return TileType::wall;
        case '+':
            return TileType::floor;
        case '.':
            return TileType::door;
        case '#':
            return TileType::corridor;
        case 'D':
            return TileType::damagedfloor;
        case '<':
            return TileType::destructible;
        case '>':
            return TileType::pebble;
        default:
            return TileType::Unused;
    };
}


class Dungeonarea {
public:

   Dungeonarea(long oldsees,int maxlength,int maxheigth,int minRoomWidth,int minRoomHeight,int maxRoomWidth,int maxRoomHeight,int mapType,int chanceRoom,int parts,
                         int xMin,int yMin, std::string name,std::string save);

    ~Dungeonarea();

    bool isLegalCell(int x, int y,const Dungeonarea &map) const;
    bool createDungeon();
    bool makeCorridor(int x,int y , int length , int direction);
    bool makeRoom(int x, int y, int xlength,int ylenghth,int direction);
    int getWidth() const;
    void setWidth(int xSixe);
    int getHeight() const;
    void setHeight(int ySize);
    int getRand(int min, int max)  ;
    const std::string &getName() const;
    void setName(const std::string &name);
    const std::string &getSave() const;
    void setSave(const std::string &save);
    TileType getcell(int x,int y) const ;
    void setcell(int x,int y,TileType type) const ;
    void saveMap(std::string mapSaveName);
    bool loadMap(std::string fileName,std::string name);
    long getOldseed() const;
    int getDungeonType() const;
    void setOldseed(long oldseed);
    int getRooms() const;

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
    int maxRoomWidth;
    int maxRoomHeight;
    int dungeonType=0;
    int chanceRoom;
    int rooms=0;
    long oldseed=0;
    std::string name;
    std::string save;
    std::vector<Tile*> tiles;
    std::ifstream ip;
    std::ofstream out;
};


#endif //MAIN_DUNGEONAREA_H
