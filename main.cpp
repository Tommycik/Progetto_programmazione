#include <iostream>
#include "Tile.h"
#include "Dungeonarea.h"
#include "Mario.h"
#include "Spawner.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Template.h"
#include <time.h>
//todo aggiungere i vettori nei vari metodi
// todo completare spawner
static const int viewHeigth = 300,viewWidth=300;
static const int width=1080,length=1920;
enum class GameEvent {
    quit, left, up, down, right, fight, magic, noop
};
void ResizeView(const sf::RenderWindow& window,sf::View& view){
float aspectRatio=float(window.getSize().x)/float (window.getSize().y);
view.setSize(viewHeigth*aspectRatio,viewHeigth);
}
class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize,Dungeonarea &map, unsigned int width, unsigned int height)
    {
        // load the tileset texture

        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber=10;
                if(map.getcell(i,j).getType()== TileType::Unused){
                    tileNumber=0;

                }else if(map.getcell(i,j).getType()== TileType::floor){
                    tileNumber=10;

                }else if(map.getcell(i,j).getType()== TileType::wall){
                    tileNumber=0;
                }else if(map.getcell(i,j).getType()== TileType::corridor){
                    tileNumber=7;
                }else if(map.getcell(i,j).getType()== TileType::door){
                    tileNumber=7;
                }
                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

int main() {

    Dungeonarea first(200, 200, 20, 20, 1, 40, 200, 50, 50);
    sf::RenderWindow window(sf::VideoMode(width, length), "try",sf::Style::Fullscreen);
    // run the program as long as the window is open
    sf::RectangleShape player(sf::Vector2f(16.0f, 16.0f));
    player.setFillColor(sf::Color::Red);
    window.setFramerateLimit(60);
    Mario* hero;
    int startX = 0;
    int startY = 0;
    first.findFreeMapTile(startX, startY, first);
    hero = new Mario(100, 1, 0, 0, "prova",20,2);
    hero->setposX(startX);
    hero->setposY(startY);
    player.setPosition(startX*16,startY*16);
    sf::View view1(sf::Vector2f (0.0f,0.0f),sf::Vector2f (viewHeigth,viewWidth));
view1.setCenter(player.getPosition());

    isLegalMove(*hero,1,-1,first);
    while (window.isOpen()) {
        TileMap map;
        if (!map.load("assets/town.png", sf::Vector2u(16, 16), first, first.getWidth(), first.getHeight()))
            return -1;

        // run the main loop
        while (window.isOpen()) {
            // handle events


            bool LeftKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::A);
            bool RightKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::D);
            bool UpKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
            bool DownKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::W);


          /*  sf::Clock WinTime;
            float Timer = WinTime.getElapsedTime();*/


            sf::Event Happen;
            while (window.pollEvent(Happen))
            {
                switch (Happen.type)
                {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::KeyPressed:
                        if (Happen.key.code == sf::Keyboard::Escape)
                            window.close();
                        break;
                    case sf::Event::Resized:
                        ResizeView(window,view1);
                        break;
                    default:
                        break;
                }
            }

            if (LeftKeyDown && isLegalMove(*hero,-1,0,first)){
                player.move(-16, 0);
view1.move(-16,0);
            hero->move(-1,0);}

            if (RightKeyDown && isLegalMove(*hero,1,0,first)){
                player.move(16, 0);
                view1.move(16,0);
            hero->move(1,0);}

            if (UpKeyDown && isLegalMove(*hero,0,1,first)){
                player.move(0, 16);
                view1.move(0,16);
            hero->move(0,1);}

            if (DownKeyDown && isLegalMove(*hero,0,-1,first)){
                player.move(0, -16);
                view1.move(0,-16);
            hero->move(0,-1);}

            // draw the map
            window.clear();
            view1.setCenter(player.getPosition());
            window.setView(view1);
            window.draw(map);
            window.draw(player);
            window.display();
        }

        return 0;
    }
}