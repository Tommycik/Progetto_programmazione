//
// Created by tommy on 30/06/2022.
//

#ifndef MAIN_LOADER_H
#define MAIN_LOADER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Spawner.h"

class TileMap : public sf::Drawable, public sf::Transformable {
public:

    bool loading(sf::Vector2u tileSize, int tileNumber, bool map, bool teleport, float j, float i);

    bool loadMap(const std::string &tileset, sf::Vector2u tileSize, Dungeonarea &map, unsigned int width,
                 unsigned int height);

    bool loaditem(sf::Vector2u tileSize, int numItem, Spawner &creator);

    bool loadTeleport(sf::Vector2u tileSize, int numItem, Spawner &creator);

    bool loadEnemy(sf::Vector2u tileSize, int numItem, Spawner &creator, bool change);

    bool loadBoss(sf::Vector2u tileSize, int numItem, Spawner &creator, bool change);

    bool loadSkill(sf::Vector2u tileSize, int numItem, std::vector<std::unique_ptr<Skills>> &skill, bool change);

    bool loadSafezone(sf::Vector2u tileSize, int numItem, Spawner &creator);

    const sf::Texture &getMTileset() const;

    bool loadTexture(const std::string &tileset);

    void loadingChange(int numItem);

    void textureLoaded();

    void figureCreation(Entity &gl, sf::Vector2u tileSize, bool skill);

private:

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    int tv = 0;
    int tu = 0;
    int count = 0;
    int textureIndex = 0;
    std::vector<std::unique_ptr<sf::RectangleShape>> figures;
    std::vector<std::unique_ptr<sf::Texture>> figuresTexture;
    std::vector<std::unique_ptr<std::string>> textureFile;
    sf::RectangleShape tries;
    sf::Vector2u textureSize;
    bool loaded = false;
    int activeEntity = 0;
    int differentTextures = 0;
    bool boss = false;
};

#endif //MAIN_LOADER_H
