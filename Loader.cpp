//
// Created by tommy on 30/06/2022.
//

#include "Loader.h"

 void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}

bool TileMap::loadSafezone ( sf::Vector2u tileSize, int numItem,Spawner &creator)
{

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize( numItem* 4);
    count=0;

    for (auto gl : creator.getSafezones()) {

        tileNumber =42*3;
        this->loading(tileSize,tileNumber,tv,tu,false,false,gl->getposY(),gl->getposX());
    }
    return true;
}

bool TileMap::loadTeleport ( sf::Vector2u tileSize, int numItem,Spawner &creator)
{

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize( numItem* 4);
    count=0;
    for (auto gl : creator.getTeleports()) {

        if(gl->isActivated()) {

            tileNumber = 0/*11*13*/;
            this->loading(tileSize,tileNumber,tv,tu,false,true,gl->getposY(),gl->getposX());
        }
    }
    return true;
}

bool TileMap::loaditem ( sf::Vector2u tileSize, int numItem,Spawner &creator)
{

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize( numItem* 4);
    count=0;

    for (auto gl : creator.getItems()) {

        if(!(gl->isTaken())) {

            tileNumber = 12;
            if (gl->getEffect() == 2) {
                tileNumber = 3;

            } else if (gl->getEffect() == 3) {
                tileNumber = 7;

            }
            this->loading(tileSize,tileNumber,tv,tu,false,false,gl->getposY(),gl->getposX());
        }
    }
    return true;
}

bool TileMap::loadMap(const std::string& tileset, sf::Vector2u tileSize, Dungeonarea &map, unsigned int width, unsigned int height)
{

    if (!m_tileset.loadFromFile(tileset))
        return false;

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);
    TileType control=TileType::Unused;
    tileNumber=0;
    tv=0;
    tu=0;
    count=0;
    int random=1;

    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            random=1;
            control=TileType::Unused;
            control=map.getcell(i, j);
            tileNumber=0;

            if(control== TileType::Unused){
                switch (map.getDungeonType()) {
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
                }
            }else if(control== TileType::floor){
                switch (map.getDungeonType()) {
                    case 0://forest
                        tileNumber=31*27-5;
                        break;
                    case 1://cave
                        tileNumber=31+11;
                        break;
                    case 2://brick
                        random=map.getRand(1,10);
                        if(random<=9){
                            tileNumber=31*6+6;
                        }else{
                            tileNumber=31*6+8;}
                        break;
                    case 3://chocolate
                        tileNumber=31*22-8;
                        break;
                    case 4://lava
                        random=map.getRand(1,5);
                        if(random<=4){
                            tileNumber=31*14+27;
                        }else{
                            tileNumber=31*13+14;}
                        break;
                    case 5://sand
                        tileNumber=31*16+27;
                        break;
                }
            }else if(control== TileType::wall){
                switch (map.getDungeonType()) {
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
                }
            }else if(control== TileType::corridor){
                switch (map.getDungeonType()) {
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
                        random=map.getRand(1,5);
                        if(random<=4){
                            tileNumber=31*14+27;
                        }else{
                            tileNumber=31*13+14;}
                        break;
                    case 5://sand
                        tileNumber=31*16+27;
                        break;
                }
            }else if(control== TileType::door){
                switch (map.getDungeonType()) {
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
                        random=map.getRand(1,5);
                        if(random<=4){
                            tileNumber=31*14+27;
                        }else{
                            tileNumber=31*13+14;
                        }
                        break;
                    case 5://sand
                        tileNumber=31*16+27;
                        break;
                }
            }
            this->loading(tileSize,tileNumber,tv,tu, true,false,j,i);
        }
    return true;
}

const sf::Texture &TileMap::getMTileset() const {
    return m_tileset;
}

bool TileMap::loading (sf::Vector2u tileSize,int tileNumber,int &tv,int &tu,bool map,bool teleport,int j,int i){

    tv=0;
    tu=0;
    int posX=i;
    int posY=j;
    int offset=1;
    if(teleport)
        offset=2;

    tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
    tv = tileNumber / (m_tileset.getSize().x / tileSize.x);
    sf::Vertex* quad = &m_vertices[(count) * 4];
    count++;

    quad[0].position = sf::Vector2f(posX * tileSize.x, posY * tileSize.y);
    quad[1].position = sf::Vector2f((posX + 1) * tileSize.x, posY * tileSize.y);
    quad[2].position = sf::Vector2f((posX + 1) * tileSize.x,(posY + 1) * tileSize.y);
    quad[3].position = sf::Vector2f(posX * tileSize.x, (posY + 1) * tileSize.y);

    quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
    quad[1].texCoords = sf::Vector2f((tu + offset) * tileSize.x, tv * tileSize.y);
    quad[2].texCoords = sf::Vector2f((tu + offset) * tileSize.x, (tv + offset) * tileSize.y);
    quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + offset) * tileSize.y);
    return true;
}
