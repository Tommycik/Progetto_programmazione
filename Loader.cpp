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

bool TileMap::loadSafezone ( sf::Vector2u tileSize, int numItem,sf::RenderWindow *window,Spawner &creator)
{



    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize( numItem* 4);
    int tileNumber=0;
    int tv=0;
    int tu=0;
    int i=0;

    for (auto gl : creator.getSafezones()) {



        tileNumber =42*3;

        tv=0;
        tu=0;

        tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
        tv = tileNumber / (m_tileset.getSize().x / tileSize.x);



        sf::Vertex* quad = &m_vertices[(i) * 4];
        i++;

        quad[0].position = sf::Vector2f(gl->getposX() * tileSize.x, gl->getposY() * tileSize.y);
        quad[1].position = sf::Vector2f((gl->getposX() + 1) * tileSize.x, gl->getposY() * tileSize.y);
        quad[2].position = sf::Vector2f((gl->getposX() + 1) * tileSize.x,
                                        (gl->getposY() + 1) * tileSize.y);
        quad[3].position = sf::Vector2f(gl->getposX() * tileSize.x, (gl->getposY() + 1) * tileSize.y);


        quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);


    }
    return true;
}

bool TileMap::loadTeleport ( sf::Vector2u tileSize, int numItem,sf::RenderWindow *window,Spawner &creator)
{



    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize( numItem* 4);
    int tileNumber=0;
    int tv=0;
    int tu=0;
    int i=0;

    for (auto gl : creator.getTeleports()) {

        if(gl->isActivated()) {

            tileNumber = 0/*11*13*/;

            tv=0;
            tu=0;

            tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            tv = tileNumber / (m_tileset.getSize().x / tileSize.x);



            sf::Vertex* quad = &m_vertices[(i) * 4];
            i++;

            quad[0].position = sf::Vector2f(gl->getposX() * tileSize.x, gl->getposY() * tileSize.y);
            quad[1].position = sf::Vector2f((gl->getposX() + 1) * tileSize.x, gl->getposY() * tileSize.y);
            quad[2].position = sf::Vector2f((gl->getposX() + 1) * tileSize.x,
                                            (gl->getposY() + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(gl->getposX() * tileSize.x, (gl->getposY() + 1) * tileSize.y);


            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 2) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 2) * tileSize.x, (tv + 2) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 2) * tileSize.y);


        }
    }
    return true;
}

bool TileMap::loaditem ( sf::Vector2u tileSize, int numItem,sf::RenderWindow *window,Spawner &creator)
{



    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize( numItem* 4);
    int tileNumber=0;
    int tv=0;
    int tu=0;
    int i=0;

    for (auto gl : creator.getItems()) {

        if(!(gl->isTaken())) {

            tileNumber = 12;
            if (gl->getEffect() == 2) {
                tileNumber = 3;

            } else if (gl->getEffect() == 3) {
                tileNumber = 7;

            }
            tv=0;
            tu=0;

            tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            sf::Vertex* quad = &m_vertices[(i) * 4];


            quad[0].position = sf::Vector2f(gl->getposX() * tileSize.x, gl->getposY() * tileSize.y);
            quad[1].position = sf::Vector2f((gl->getposX() + 1) * tileSize.x, gl->getposY() * tileSize.y);
            quad[2].position = sf::Vector2f((gl->getposX() + 1) * tileSize.x,
                                            (gl->getposY() + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(gl->getposX() * tileSize.x, (gl->getposY() + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            i++;

        }
    }
    return true;
}

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize,const Dungeonarea &map, unsigned int width, unsigned int height)
{


    if (!m_tileset.loadFromFile(tileset))
        return false;


    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);
    int tileNumber=0;
    int tv=0;
    int tu=0;
    TileType control=TileType::Unused;

    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            control=TileType::Unused;
            control=map.getcell(i, j);
            tileNumber=10;
            if(control== TileType::Unused){
                tileNumber=0;

            }else if(control== TileType::floor){
                tileNumber=10;

            }else if(control== TileType::wall){
                tileNumber=0;
            }else if(control== TileType::corridor){
                tileNumber=7;
            }else if(control== TileType::door){
                tileNumber=7;
            }
            tv=0;
            tu=0;

            tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            tv = tileNumber / (m_tileset.getSize().x / tileSize.x);


            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];


            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);


            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);



        }
    return true;
}

const sf::Texture &TileMap::getMTileset() const {
    return m_tileset;
}
