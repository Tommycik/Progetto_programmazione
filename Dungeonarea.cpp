//
// Created by tommy on 16/06/2022.
//

#include "Dungeonarea.h"
//todo rimettere save e name

Dungeonarea::Dungeonarea(long oldseed,int maxLength, int maxHeigth, int minRoomWidth, int minRoomHeight,
                         int mapType, int chanceRoom, int parts, int xMin, int yMin, std::string name,
std::string save) : xMax(maxLength),yMax(maxHeigth),
                                                                                       minRoomWidth(minRoomWidth),
                                                                                       minRoomHeight(minRoomHeight),
                                                                                       dungeonType(mapType),
                                                                                       chanceRoom(chanceRoom),
                                                                                       parts(parts), xMin(xMin),
                                                                                               yMin(yMin) {
    this->tiles = nullptr;
    this->oldseed=oldseed;
    this->createDungeon(getRand(xMin, xMax), getRand(yMin, yMax), parts);
    this->name=name;
    this->save=save;
}


Dungeonarea::~Dungeonarea() {
    if (tiles)
        delete[] tiles;
}

int Dungeonarea::getRand(int min, int max) {
    long seed = time(NULL) + oldseed;
    oldseed = seed;

    srand(seed);
    int n = max - min + 1;
    int i = rand() % n; // 0 < i < n
    if (i < 0)
        i = -i;
    return min + i;
}

int Dungeonarea::getWidth() const {
    return width;
}

void Dungeonarea::setWidth(int xSixe) {
    Dungeonarea::width = xSixe;
}

int Dungeonarea::getHeight() const {
    return height;
}

void Dungeonarea::setHeight(int ySize) {
    Dungeonarea::height = ySize;
}

bool Dungeonarea::makeCorridor(int x, int y, int length, int direction) {
    int len = getRand(2, length);
    TileType floor = TileType::corridor;
    int dir = 0;
    if (direction > 0 && direction < 4)
        dir = direction;

    int xtemp = 0;
    int ytemp = 0;

    switch (dir) {
        case 0:
            //north
            //check if there's enough space for the corridor
            //start with checking it's not out of the boundaries
            if (x < 0 || x > width)
                return false;
            else
                xtemp = x;

            //same thing here, to make sure it's not out of the boundaries
            for (ytemp = y; ytemp > (y - len); ytemp--) {
                if (ytemp < 0 || ytemp > height)
                    return false; // out of boundaries
                if (tiles[xtemp + width * ytemp].getType() != TileType::Unused)
                    return false;
            }

            //if we're still here, let's start building
            for (ytemp = y; ytemp > (y - len); ytemp--) {
                tiles[xtemp + width * ytemp].setType(TileType::corridor);
            }
            break;
        case 1:
            //east
            if (y < 0 || y > height)
                return false;
            else
                ytemp = y;

            for (xtemp = x; xtemp < (x + len); xtemp++) {
                if (xtemp < 0 || xtemp > width)
                    return false;
                if (tiles[xtemp + width * ytemp].getType() != TileType::Unused)
                    return false;
            }

            for (xtemp = x; xtemp < (x + len); xtemp++) {
                tiles[xtemp + width * ytemp].setType(TileType::corridor);
            }
            break;
        case 2:
            //south
            if (x < 0 || x > width)
                return false;
            else
                xtemp = x;

            for (ytemp = y; ytemp < (y + len); ytemp++) {
                if (ytemp < 0 || ytemp > height)
                    return false;
                if (tiles[xtemp + width * ytemp].getType() != TileType::Unused)
                    return false;
            }

            for (ytemp = y; ytemp < (y + len); ytemp++) {
                tiles[xtemp + width * ytemp].setType(TileType::corridor);
            }
            break;
        case 3:
            //west
            if (ytemp < 0 || ytemp > height)
                return false;
            else
                ytemp = y;

            for (xtemp = x; xtemp > (x - len); xtemp--) {
                if (xtemp < 0 || xtemp > width)
                    return false;
                if (tiles[xtemp + width * ytemp].getType() != TileType::Unused)
                    return false;
            }

            for (xtemp = x; xtemp > (x - len); xtemp--) {
                tiles[xtemp + width * ytemp].setType(TileType::corridor);
            }
            break;
    }

    // Successful build
    return true;
}

bool Dungeonarea::makeRoom(int x, int y, int xlength, int ylength, int direction) {
    int xlen = getRand(minRoomWidth, xlength);
    int ylen = getRand(minRoomHeight, ylength);
    //the tile type it's going to be filled with
    TileType floor = TileType::floor;
    TileType wall = TileType::wall;
    //choose the way it's pointing at
    int dir = 0;
    if (direction > 0 && direction < 4)
        dir = direction;

    switch (dir) {
        case 0:
            //north
            //Check if there's enough space left for it
            for (int ytemp = y; ytemp > (y - ylen); ytemp--) {
                if (ytemp < 0 || ytemp > height)
                    return false;
                for (int xtemp = (x - xlen / 2); xtemp < (x + (xlen + 1) / 2);
                     xtemp++) {
                    if (xtemp < 0 || xtemp > width)
                        return false;
                    if (tiles[xtemp + width * ytemp].getType() != TileType::Unused)
                        return false; //no space left...
                }
            }

            //we're still here, build
            for (int ytemp = y; ytemp > (y - ylen); ytemp--) {
                for (int xtemp = (x - xlen / 2); xtemp < (x + (xlen + 1) / 2);
                     xtemp++) {
                    //start with the walls
                    if (xtemp == (x - xlen / 2))
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                    else if (xtemp == (x + (xlen - 1) / 2))
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                    else if (ytemp == y)
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                    else if (ytemp == (y - ylen + 1))
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                        //and then fill with the floor
                    else
                        tiles[xtemp + width * ytemp].setType(TileType::floor);
                }
            }
            break;
        case 1:
            //east
            for (int ytemp = (y - ylen / 2); ytemp < (y + (ylen + 1) / 2);
                 ytemp++) {
                if (ytemp < 0 || ytemp > height)
                    return false;
                for (int xtemp = x; xtemp < (x + xlen); xtemp++) {
                    if (xtemp < 0 || xtemp > width)
                        return false;
                    if (tiles[xtemp + width * ytemp].getType() != TileType::Unused)
                        return false;
                }
            }

            for (int ytemp = (y - ylen / 2); ytemp < (y + (ylen + 1) / 2);
                 ytemp++) {
                for (int xtemp = x; xtemp < (x + xlen); xtemp++) {

                    if (xtemp == x)
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                    else if (xtemp == (x + xlen - 1))
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                    else if (ytemp == (y - ylen / 2))
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                    else if (ytemp == (y + (ylen - 1) / 2))
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                    else
                        tiles[xtemp + width * ytemp].setType(TileType::floor);
                }
            }
            break;
        case 2:
            //south
            for (int ytemp = y; ytemp < (y + ylen); ytemp++) {
                if (ytemp < 0 || ytemp > height)
                    return false;
                for (int xtemp = (x - xlen / 2); xtemp < (x + (xlen + 1) / 2);
                     xtemp++) {
                    if (xtemp < 0 || xtemp > width)
                        return false;
                    if (tiles[xtemp + width * ytemp].getType() != TileType::Unused)
                        return false;
                }
            }

            for (int ytemp = y; ytemp < (y + ylen); ytemp++) {
                for (int xtemp = (x - xlen / 2); xtemp < (x + (xlen + 1) / 2);
                     xtemp++) {

                    if (xtemp == (x - xlen / 2))
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                    else if (xtemp == (x + (xlen - 1) / 2))
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                    else if (ytemp == y)
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                    else if (ytemp == (y + ylen - 1))
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                    else
                        tiles[xtemp + width * ytemp].setType(TileType::floor);
                }
            }
            break;
        case 3:
            //west
            for (int ytemp = (y - ylen / 2); ytemp < (y + (ylen + 1) / 2);
                 ytemp++) {
                if (ytemp < 0 || ytemp > height)
                    return false;
                for (int xtemp = x; xtemp > (x - xlen); xtemp--) {
                    if (xtemp < 0 || xtemp > width)
                        return false;
                    if (tiles[xtemp + width * ytemp].getType() != TileType::Unused)
                        return false;
                }
            }

            for (int ytemp = (y - ylen / 2); ytemp < (y + (ylen + 1) / 2);
                 ytemp++) {
                for (int xtemp = x; xtemp > (x - xlen); xtemp--) {

                    if (xtemp == x)
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                    else if (xtemp == (x - xlen + 1))
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                    else if (ytemp == (y - ylen / 2))
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                    else if (ytemp == (y + (ylen - 1) / 2))
                        tiles[xtemp + width * ytemp].setType(TileType::wall);
                    else
                        tiles[xtemp + width * ytemp].setType(TileType::floor);
                }
            }
            break;
    }

    // successful build
    return true;
}

bool Dungeonarea::createDungeon(int xLength, int yLength, int inobj) {
    if (inobj < 1)
        parts = 10;
    else
        parts = inobj;

    //adjust the size of the map, if it's smaller or bigger than the limits
    if (xLength < xMin)
        width = xMin;
    else if (xLength > xMax)
        width = xMax;
    else
        width = xLength;

    if (yLength < yMin)
        height = yMin;
    else if (yLength > yMax)
        height = yMax;
    else
        height = yLength;

    //redefine the map var, so it's adjusted to our new map size
    tiles = new Tile[width * height];

    //start with making the "standard stuff" on the map
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            //ie, making the borders of unwalkable walls
            if (y == 0)
                tiles[x + width * y].setType(TileType::wall);
            else if (y == height - 1)
                tiles[x + width * y].setType(TileType::wall);
            else if (x == 0)
                tiles[x + width * y].setType(TileType::wall);
            else if (x == width - 1)
                tiles[x + width * y].setType(TileType::wall);

                //and fill the rest with dirt
            else
                tiles[x + width * y].setType(TileType::Unused);
        }
    }

    /*******************************************************************************
     And now the code of the random-map-generation-algorithm begins!
     *******************************************************************************/

    //start with making a room in the middle, which we can start building upon
    makeRoom(width / 2, height / 2, 10, 8, getRand(0, 3)); //getrand saken f????r att slumpa fram riktning p?? rummet

    //keep count of the number of "objects" we've made
    int currentFeatures = 1; //+1 for the first room we just made

    //then we start the main loop
    for (int countingTries = 0; countingTries < 1000; countingTries++) {
        //check if we've reached our quota
        if (currentFeatures == parts) {
            break;
        }

        //start with a random wall
        int newx = 0;
        int xmod = 0;
        int newy = 0;
        int ymod = 0;
        int validTile = -1;
        //1000 chances to find a suitable object (room or corridor)..
        //(yea, i know it's kinda ugly with a for-loop... -_-')
        for (int testing = 0; testing < 1000; testing++) {
            newx = getRand(1, width - 1);
            newy = getRand(1, height - 1);
            validTile = -1;
            //cout<<"tempx: " << newx << "\ttempy: " << newy<<endl;
            if (tiles[newx + width * newy].getType() == TileType::wall
                || tiles[newx + width * newy].getType() == TileType::corridor) {
                //check if we can reach the place
                if (tiles[newx + width * (newy + 1)].getType() == TileType::floor
                    || tiles[newx + width * (newy + 1)].getType() == TileType::corridor) {
                    validTile = 0; //
                    xmod = 0;
                    ymod = -1;
                } else if (tiles[newx - 1 + width * newy].getType() == TileType::floor
                           || tiles[newx - 1 + width * newy].getType() == TileType::corridor) {
                    validTile = 1; //
                    xmod = +1;
                    ymod = 0;
                } else if (tiles[newx + width * (newy - 1)].getType() == TileType::floor
                           || tiles[newx + width * (newy - 1)].getType() == TileType::corridor) {
                    validTile = 2; //
                    xmod = 0;
                    ymod = +1;
                } else if (tiles[newx + 1 + width * newy].getType() == TileType::floor
                           || tiles[newx + 1 + width * newy].getType() == TileType::corridor) {
                    validTile = 3; //
                    xmod = -1;
                    ymod = 0;
                }

                //check that we haven't got another door nearby, so we won't get a lot of openings besides
                //each other
                if (validTile > -1) {
                    if (tiles[newx + width * (newy + 1)].getType() == TileType::door) //north
                        validTile = -1;
                    else if (tiles[newx - 1 + width * newy].getType() == TileType::door) //east
                        validTile = -1;
                    else if (tiles[newx + width * (newy - 1)].getType() == TileType::door) //south
                        validTile = -1;
                    else if (tiles[newx + 1 + width * newy].getType() == TileType::door) //west
                        validTile = -1;
                }

                //if we can, jump out of the loop and continue with the rest
                if (validTile > -1)
                    break;
            }
        }
        if (validTile > -1) {
            //choose what to build now at our newly found place, and at what direction
            int feature = getRand(0, 100);
            if (feature <= chanceRoom) { //a new room
                if (makeRoom((newx + xmod), (newy + ymod), 8, 6, validTile)) {
                    currentFeatures++; //add to our quota

                    //then we mark the wall opening with a door
                    tiles[newx + width * newy].setType(TileType::door);

                    //clean up in front of the door so we can reach it
                    tiles[newx + xmod + width * (newy + ymod)].setType(TileType::floor);
                }
            } else if (feature >= chanceRoom) { //new corridor
                if (makeCorridor((newx + xmod), (newy + ymod), 6, validTile)) {
                    //same thing here, add to the quota and a door
                    currentFeatures++;

                    tiles[newx + width * newy].setType(TileType::door);
                }
            }
        }
    }
}

TileType Dungeonarea::getcell(int x, int y) const {
    return tiles[x + width * y].getType();
}

bool Dungeonarea::isLegalCell(int x, int y,const Dungeonarea &map) const{
    TileType cell = map.getcell(x, y);
    switch (cell) {
        case TileType::Unused:
            return false;
        case TileType::wall:
            return false;
        case TileType::floor:
            return true;
        case TileType::corridor:
            return true;
        case TileType::door:
            return true;
        case TileType::damagedfloor:
            return true;
        default:
            return false;
    }
}

const std::string &Dungeonarea::getName() const {
    return name;
}

void Dungeonarea::setName(const std::string &name) {
    Dungeonarea::name = name;
}

const std::string &Dungeonarea::getSave() const {
    return save;
}

void Dungeonarea::setSave(const std::string &save) {
    Dungeonarea::save = save;
}

void Dungeonarea::saveMap(std::string mapSaveName) {
    std::ofstream out;
   out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
   // try {
        out.open(mapSaveName);
        out << name << std::endl;
        out << width << "\n" << height << std::endl;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                out << TileTypeToTileString(getcell(x, y));
            }
            out << std::endl;
        }
        out.close();
    //}
}

void Dungeonarea::setcell(int x, int y, TileType type) const {
    tiles[x + width * y].setType(type);
}

bool Dungeonarea::loadMap(std::string fileName,std::string name) {
    std::ifstream in;

    in.exceptions(std::ifstream::failbit);
    try {
        in.open(fileName);
    } catch (std::ios_base::failure& e) {

       return false;
    }
    std::string fileLine;
    std::getline(in, fileLine);
    if (fileLine.compare(name) != 0)
        throw GameFileException("Map file is in wrong format", fileName, true);

    std::getline(in, fileLine);

    width = std::stoi(fileLine);
    std::getline(in, fileLine);

    height = std::stoi(fileLine);
    std::getline(in, fileLine);
    int y = 0;
    char c;

    tiles=new Tile[width*height];
    while(!in.eof() /*&& std::getline(in, fileLine)*/) {
        for (int x = 0; x < width; x++) {
            try {

                c=fileLine.at(x);
                TileType cellType = TileStringToTileType(c);
                tiles[x+width*y].setType(cellType);

            } catch (std::out_of_range &e) {
                throw std::out_of_range("Can not set map tile at x: " + std::to_string(x)+" - y: " + std::to_string(y));
            }
        }

        y++;
        if(y==height){
            break;
        }else{
        std::getline(in, fileLine);}
    }
    if (y!=height)
        throw std::runtime_error("Map height size wrong. Expected "+std::to_string(height)+" but read: " + std::to_string(y));

    in.close();
    return true;
}

long Dungeonarea::getOldseed() const {
    return oldseed;
}

void Dungeonarea::setOldseed(long oldseed) {
    Dungeonarea::oldseed = oldseed;
}




