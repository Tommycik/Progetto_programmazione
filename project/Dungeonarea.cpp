//
// Created by tommy on 16/06/2022.
//

#include "Dungeonarea.h"


Dungeonarea::Dungeonarea(long oldseed,int maxLength, int maxHeigth, int minRoomWidth, int minRoomHeight,int maxRoomWidth,int maxRoomHeight,
                         int mapType, int chanceRoom, int parts, int xMin, int yMin, std::string name,
std::string save,int minRooms) : xMax(maxLength),yMax(maxHeigth),minRoomWidth(minRoomWidth),minRoomHeight(minRoomHeight),
parts(parts), xMin(xMin),yMin(yMin),maxRoomHeight(maxRoomHeight),maxRoomWidth(maxRoomWidth) {
    this->oldseed=oldseed;
    this->name=name;
    this->save=save;
    this->rooms=minRooms;
    this->dungeonType=mapType;
    this->chanceRoom=chanceRoom;//this->getRand(40,80);
}


Dungeonarea::~Dungeonarea() {

}

int Dungeonarea::getRand(int min, int max) {
    long seed = time(NULL) + oldseed;
    this->oldseed = seed;

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
    this->width = xSixe;
}

int Dungeonarea::getHeight() const {
    return height;
}

void Dungeonarea::setHeight(int ySize) {
    this->height = ySize;
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
                if (tiles[xtemp + width * ytemp]->getType() != TileType::Unused)
                    return false;
            }

            //if we're still here, let's start building
            for (ytemp = y; ytemp > (y - len); ytemp--) {
                tiles[xtemp + width * ytemp]->setType(TileType::corridor,this->dungeonType);
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
                if (tiles[xtemp + width * ytemp]->getType() != TileType::Unused)
                    return false;
            }

            for (xtemp = x; xtemp < (x + len); xtemp++) {
                tiles[xtemp + width * ytemp]->setType(TileType::corridor,this->dungeonType);
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
                if (tiles[xtemp + width * ytemp]->getType() != TileType::Unused)
                    return false;
            }

            for (ytemp = y; ytemp < (y + len); ytemp++) {
                tiles[xtemp + width * ytemp]->setType(TileType::corridor,this->dungeonType);
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
                if (tiles[xtemp + width * ytemp]->getType() != TileType::Unused)
                    return false;
            }

            for (xtemp = x; xtemp > (x - len); xtemp--) {
                tiles[xtemp + width * ytemp]->setType(TileType::corridor,this->dungeonType);
            }
            break;
    }

    // Successful build
    return true;
}

bool Dungeonarea::makeRoom(int x, int y, int xlength, int ylength, int direction) {
    int xlen = getRand(minRoomWidth, maxRoomWidth);
    int ylen = getRand(minRoomHeight, maxRoomHeight);
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
                    if (tiles[xtemp + width * ytemp]->getType() != TileType::Unused)
                        return false; //no space left...
                }
            }

            //we're still here, build
            for (int ytemp = y; ytemp > (y - ylen); ytemp--) {
                for (int xtemp = (x - xlen / 2); xtemp < (x + (xlen + 1) / 2);
                     xtemp++) {
                    //start with the walls
                    if (xtemp == (x - xlen / 2))
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                    else if (xtemp == (x + (xlen - 1) / 2))
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                    else if (ytemp == y)
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                    else if (ytemp == (y - ylen + 1))
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                        //and then fill with the floor
                    else
                        tiles[xtemp + width * ytemp]->setType(TileType::floor,this->dungeonType);
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
                    if (tiles[xtemp + width * ytemp]->getType() != TileType::Unused)
                        return false;
                }
            }

            for (int ytemp = (y - ylen / 2); ytemp < (y + (ylen + 1) / 2);
                 ytemp++) {
                for (int xtemp = x; xtemp < (x + xlen); xtemp++) {

                    if (xtemp == x)
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                    else if (xtemp == (x + xlen - 1))
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                    else if (ytemp == (y - ylen / 2))
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                    else if (ytemp == (y + (ylen - 1) / 2))
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                    else
                        tiles[xtemp + width * ytemp]->setType(TileType::floor,this->dungeonType);
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
                    if (tiles[xtemp + width * ytemp]->getType() != TileType::Unused)
                        return false;
                }
            }

            for (int ytemp = y; ytemp < (y + ylen); ytemp++) {
                for (int xtemp = (x - xlen / 2); xtemp < (x + (xlen + 1) / 2);
                     xtemp++) {

                    if (xtemp == (x - xlen / 2))
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                    else if (xtemp == (x + (xlen - 1) / 2))
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                    else if (ytemp == y)
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                    else if (ytemp == (y + ylen - 1))
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                    else
                        tiles[xtemp + width * ytemp]->setType(TileType::floor,this->dungeonType);
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
                    if (tiles[xtemp + width * ytemp]->getType() != TileType::Unused)
                        return false;
                }
            }

            for (int ytemp = (y - ylen / 2); ytemp < (y + (ylen + 1) / 2);
                 ytemp++) {
                for (int xtemp = x; xtemp > (x - xlen); xtemp--) {

                    if (xtemp == x)
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                    else if (xtemp == (x - xlen + 1))
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                    else if (ytemp == (y - ylen / 2))
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                    else if (ytemp == (y + (ylen - 1) / 2))
                        tiles[xtemp + width * ytemp]->setType(TileType::wall,this->dungeonType);
                    else
                        tiles[xtemp + width * ytemp]->setType(TileType::floor,this->dungeonType);
                }
            }
            break;
    }

    // successful build
    return true;
}

bool Dungeonarea::createDungeon() {
    int actualRooms=0;

    if (parts < 1)
        parts = 10;

    //adjust the size of the map, if it's smaller or bigger than the limits
    int xLength=getRand(xMin, xMax);
    int yLength=getRand(yMin, yMax);
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

do{

    this->tiles.clear();
    this-> tiles.reserve(width * height);
    for(int i=0;i<width * height;i++){
        auto newTile = std::make_unique<Tile>();
        tiles.emplace_back(std::move(newTile));
    }



    //redefine the map var, so it's adjusted to our new map size


    actualRooms=0;

    //start with making the "standard stuff" on the map
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            //ie, making the borders of unwalkable walls
            if (y == 0)
                tiles[x + width * y]->setType(TileType::wall,this->dungeonType);
            else if (y == height - 1)
                tiles[x + width * y]->setType(TileType::wall,this->dungeonType);
            else if (x == 0)
                tiles[x + width * y]->setType(TileType::wall,this->dungeonType);
            else if (x == width - 1)
                tiles[x + width * y]->setType(TileType::wall,this->dungeonType);

                //and fill the rest with dirt
            else
                tiles[x + width * y]->setType(TileType::Unused,this->dungeonType);
        }
    }


    //start with making a room ip the middle, which we can start building upon
    makeRoom(width / 2, height / 2, 10, 8, getRand(0, 3));
    actualRooms++;
    //keep count of the number of "objects" we've made
    int currentFeatures = 1; //+1 for the first room we just made

    //then we start the main loop
    for (int countingTries = 0; countingTries < 100000000; countingTries++) {
        //check if we've reached our quota
        if (currentFeatures == parts) {
            return true;
        }
        if(actualRooms==rooms)
            return true;

        //start with a random wall
        int newx = 0;
        int xmod = 0;
        int newy = 0;
        int ymod = 0;
        int validTile = -1;

        for (int testing = 0; testing < 100000000; testing++) {
            newx = getRand(1, width - 2);
            newy = getRand(1, height - 2);
            validTile = -1;

            if (tiles[newx + width * newy]->getType() == TileType::wall
                || tiles[newx + width * newy]->getType() == TileType::corridor) {
                //check if we can reach the place
                if (tiles[newx + width * (newy + 1)]->getType() == TileType::floor
                    || tiles[newx + width * (newy + 1)]->getType() == TileType::corridor) {
                    validTile = 0; //
                    xmod = 0;
                    ymod = -1;
                } else if (tiles[newx - 1 + width * newy]->getType() == TileType::floor
                           || tiles[newx - 1 + width * newy]->getType() == TileType::corridor) {
                    validTile = 1; //
                    xmod = +1;
                    ymod = 0;
                } else if (tiles[newx + width * (newy - 1)]->getType() == TileType::floor
                           || tiles[newx + width * (newy - 1)]->getType() == TileType::corridor) {
                    validTile = 2; //
                    xmod = 0;
                    ymod = +1;
                } else if (tiles[newx + 1 + width * newy]->getType() == TileType::floor
                           || tiles[newx + 1 + width * newy]->getType() == TileType::corridor) {
                    validTile = 3; //
                    xmod = -1;
                    ymod = 0;
                }


                if (validTile > -1) {
                    if (tiles[newx + width * (newy + 1)]->getType() == TileType::door) //north
                        validTile = -1;
                    else if (tiles[newx - 1 + width * newy]->getType() == TileType::door) //east
                        validTile = -1;
                    else if (tiles[newx + width * (newy - 1)]->getType() == TileType::door) //south
                        validTile = -1;
                    else if (tiles[newx + 1 + width * newy]->getType() == TileType::door) //west
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
                    actualRooms++;
                    //then we mark the wall opening with a door
                    tiles[newx + width * newy]->setType(TileType::door,this->dungeonType);

                    //clean up ip front of the door so we can reach it
                    tiles[newx + xmod + width * (newy + ymod)]->setType(TileType::floor,this->dungeonType);
                }
            } else if (feature >= chanceRoom) { //new corridor
                if (makeCorridor((newx + xmod), (newy + ymod), 6, validTile)) {
                    //same thing here, add to the quota and a door
                    currentFeatures++;

                    tiles[newx + width * newy]->setType(TileType::door,this->dungeonType);
                }
            }
        }
    }
    if(actualRooms>=rooms)
        return true;
}while (actualRooms<rooms);

}

TileType Dungeonarea::getcell(int x, int y) const {
    return tiles[x + width * y]->getType();
}

bool Dungeonarea::isLegalCell(int x, int y) const{


}

const std::string &Dungeonarea::getName() const {
    return name;
}

void Dungeonarea::setName(const std::string &name) {
    this->name = name;
}

const std::string &Dungeonarea::getSave() const {
    return save;
}

void Dungeonarea::setSave(const std::string &save) {
    this->save = save;
}

void Dungeonarea::saveMap(std::string mapSaveName) {

   out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
   // try {
        out.open(mapSaveName,std::ios_base::trunc);
        out << name << std::endl;
        out << width << "\n" << height << "\n"<<dungeonType<< "\n"<<rooms<< "\n"<<maxRoomHeight<< "\n"<<maxRoomWidth<<std::endl;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                out << TileTypeToTileString(this->getcell(x, y));
            }
            out << std::endl;
        }
        out.close();
    //}
}

void Dungeonarea::setcell(int x, int y, TileType type) const {
    tiles[x + width * y]->setType(type,this->dungeonType);
}

bool Dungeonarea::loadMap(std::string fileName,std::string name) {

    ip.exceptions(std::ifstream::failbit);
    try {
        ip.open(fileName);
    } catch (std::ios_base::failure& e) {

       return false;
    }
    std::string fileLine=" ";
    std::getline(ip, fileLine);
    if (fileLine.compare(name) != 0)
        throw GameFileException("Map file is ip wrong format", fileName, true);

    std::getline(ip, fileLine);

    width = std::stoi(fileLine);
    std::getline(ip, fileLine);

    height = std::stoi(fileLine);
    std::getline(ip, fileLine);
    dungeonType = std::stoi(fileLine);
    std::getline(ip, fileLine);
    rooms = std::stoi(fileLine);
    std::getline(ip, fileLine);
    maxRoomHeight = std::stoi(fileLine);
    std::getline(ip, fileLine);
    maxRoomWidth = std::stoi(fileLine);
    std::getline(ip, fileLine);
    int y = 0;
    char c;

    this->tiles.clear();
    this->tiles.reserve(width * height);
    for(int i=0;i<width * height;i++){
        auto newTile = std::make_unique<Tile>();
        tiles.emplace_back(std::move(newTile));
    }

    while(!ip.eof() /*&& std::getline(ip, fileLine)*/) {
        for (int x = 0; x < width; x++) {
            try {

                c=fileLine.at(x);
                TileType cellType = TileStringToTileType(c);
                tiles[x+width*y]->setType(cellType,this->dungeonType);

            } catch (std::out_of_range &e) {
                throw std::out_of_range("Can not set map tile at x: " + std::to_string(x)+" - y: " + std::to_string(y));
            }
        }

        y++;
        if(y==height){
            break;
        }else{
        std::getline(ip, fileLine);}
    }
    if (y!=height)
        throw std::runtime_error("Map height size wrong. Expected "+std::to_string(height)+" but read: " + std::to_string(y));

    ip.close();
    return true;
}

long Dungeonarea::getOldseed() const {
    return oldseed;
}

void Dungeonarea::setOldseed(long oldseed) {
    this->oldseed = oldseed;
}

int Dungeonarea::getDungeonType() const {
    return dungeonType;
}

int Dungeonarea::getRooms() const {
    return rooms;
}

bool Dungeonarea::getPassable(float futureX,float futureY) const {
    bool halfY = false;
    bool halfX = false;
    bool quarterX = false;
    bool quarterY = false;
    float xTemp = (futureX / 0.25);
    float yTemp = (futureY / 0.25);
    int xPass = xTemp;
    int yPass = yTemp;
    int passingX = xPass % 4;
    int passingY = yPass % 4;
    float finalX = 0;
    float finalY = 0;
    if (passingX * 0.25 != 0) {
        if (passingX * 0.25 <= 0.25) {
            quarterX = true;
            //futureX=futureX-passingX*0.25;
        } else if (passingX * 0.25 >= 0.75) {
            finalX = 1 - passingX * 0.25;
            futureX = futureX + finalX;
        } else if (passingX * 0.25 == 0.50) {
            halfX = true;
        }
    }

        if (passingY * 0.25 != 0) {
            if (passingY * 0.25 <= 0.25) {
                quarterY = true;

            } else if (passingY * 0.25 >= 0.75) {
                finalY = 1 - passingY * 0.25;
                futureY = futureY + finalY;
            } else if (passingY * 0.25 == 0.50) {
                halfY = true;

            }

        }

        if (halfX == false && halfY == false) {

            if (quarterX == true && quarterY == false) {
                return (tiles[futureX + 0.25 + width * (futureY)]->isPassable() &&
                        tiles[futureX - 0.25 + width * (futureY)]->isPassable());
            } else if (quarterX == false && quarterY == true) {
                return (tiles[futureX + width * (futureY + 0.25)]->isPassable() &&
                        tiles[futureX + width * (futureY - 0.25)]->isPassable());
            } else if (quarterX == true && quarterY == true) {
                return (tiles[futureX + 0.25 + width * (futureY + 0.25)]->isPassable() &&
                        tiles[futureX - 0.25 + width * (futureY - 0.25)]->isPassable() &&
                        tiles[futureX + 0.25 + width * (futureY - 0.25)]->isPassable() &&
                        tiles[futureX - 0.25 + width * (futureY + 0.25)]->isPassable());

            }
            return tiles[futureX + width * futureY]->isPassable();
        } else if (halfX == true && halfY == false) {

            if (quarterY == true) {
                return (tiles[futureX + 0.5 + width * (futureY + 0.25)]->isPassable() &&
                        tiles[futureX - 0.5 + width * (futureY - 0.25)]->isPassable());
            }

            return (tiles[futureX + 0.5 + width * (futureY)]->isPassable() &&
                    tiles[futureX - 0.5 + width * (futureY)]->isPassable());

        } else if (halfX == false && halfY == true) {

            if (quarterX == true) {
                return (tiles[futureX + 0.25 + width * (futureY + 0.5)]->isPassable() &&
                        tiles[futureX - 0.25 + width * (futureY - 0.5)]->isPassable());
            }
            return (tiles[futureX + width * (futureY + 0.5)]->isPassable() &&
                    tiles[futureX + width * (futureY - 0.5)]->isPassable());
        } else if (halfX == true && halfY == true) {
            return (tiles[futureX + 0.5 + width * (futureY + 0.5)]->isPassable() &&
                    tiles[futureX - 0.5 + width * (futureY - 0.5)]->isPassable() &&
                    tiles[futureX + 0.5 + width * (futureY - 0.5)]->isPassable() &&
                    tiles[futureX - 0.5 + width * (futureY + 0.5)]->isPassable());

        }

}

bool Dungeonarea::getSpawnPlace(int x ,int y) const{
    tiles[x + width * y]->isSpawnPlace();
}

int Dungeonarea::getTileNumber(int x, int y) const {
    tiles[x + width * y]->getTileNumber();
}


TileType TileStringToTileType(const char &tile){
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

std::string TileTypeToTileString(const TileType &tile)  {
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
