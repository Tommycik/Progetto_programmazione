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

    for (auto &gl : creator.getSafezones()) {
        this->loading(tileSize,gl->getTileNumber(),false,false,gl->getposY(),gl->getposX());
    }
    return true;
}

bool TileMap::loadTeleport ( sf::Vector2u tileSize, int numItem,Spawner &creator)
{

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize( numItem* 4);
    count=0;
    for (auto &gl : creator.getTeleports()) {

        if(gl->isActivated()) {
            this->loading(tileSize,gl->getTileNumber(),false,true,gl->getposY(),gl->getposX());
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

    for (auto &gl : creator.getItems()) {
        if(!(gl->isTaken())) {
            this->loading(tileSize,gl->getTileNumber(),false,false,gl->getposY(),gl->getposX());
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
    tv=0;
    tu=0;
    count=0;

    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j){
            this->loading(tileSize,map.getTileNumber(i,j),true,false,j,i);
        }
    return true;
}

const sf::Texture &TileMap::getMTileset() const {
    return m_tileset;
}

bool TileMap::loading (sf::Vector2u tileSize,int tileNumber,bool map,bool teleport,float j,float i){


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


