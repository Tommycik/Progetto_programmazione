//
// Created by tommy on 30/06/2022.
//

#ifndef MAIN_LOADER_H
#define MAIN_LOADER_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Dungeonarea.h"
#include "Spawner.h"


    class TileMap : public sf::Drawable, public sf::Transformable {
    public:

        bool load(const std::string& tileset, sf::Vector2u tileSize, Dungeonarea &map, unsigned int width, unsigned int height);
        bool loadTexture(const std::string& tileset){
            if (!m_tileset.loadFromFile(tileset))
                return false;
            return true;
        }

        const sf::Texture &getMTileset() const;

        bool loaditem ( sf::Vector2u tileSize, int numItem,sf::RenderWindow *window,Spawner &creator);


        bool loadTeleport ( sf::Vector2u tileSize, int numItem,sf::RenderWindow *window,Spawner &creator);


        bool loadSafezone ( sf::Vector2u tileSize, int numItem,Spawner &creator);
    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::VertexArray m_vertices;
        sf::Texture m_tileset;

    };



#endif //MAIN_LOADER_H
