#include <iostream>
#include "Tile.h"
#include "Dungeonarea.h"
#include "Mario.h"
#include "Spawner.h"
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Template.h"
#include <string>

#include <ctime>
//todo aggiungere i vettori nei vari metodi
// todo completare spawner
//todo rendere più veloce l'applicazione
//todo implementare oggetti
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

    window.setFramerateLimit(100);
    Mario* hero;
    int startX = 0;
    int startY = 0;
    findFreeMapTile(startX, startY, first);
    hero = new Mario(100, 1, 0, 0, "prova",40,2);
    sf::RectangleShape life(sf::Vector2f(hero->getHp()/10*16.0f, 7.0f));
    sf::RectangleShape stamina(sf::Vector2f(hero->getStamina()/10*16.0f, 7.0f));
    life.setFillColor(sf::Color::Red);
    sf::Font myFont;
    sf::Text Potion;
    Potion.setFont(myFont);

    Potion.setFillColor(sf::Color::White);
    Potion.setCharacterSize(128);
    Potion.setScale(sf::Vector2f(0.1,0.1));
    Potion.setOutlineColor(sf::Color::Black);
    Potion.setOutlineThickness(1);




    if (!myFont.loadFromFile("../assets/arial.ttf"))
    {
        return -1;
    }
    stamina.setFillColor(sf::Color::Yellow);
    life.setOutlineColor(sf::Color::Black);
    life.setOutlineThickness(1);
    stamina.setOutlineColor(sf::Color::Black);
    stamina.setOutlineThickness(1);
    hero->setposX(startX);
    hero->setposY(startY);
    player.setPosition(int(startX*16),int(startY*16));

    sf::View view1(sf::Vector2f (0.0f,0.0f),sf::Vector2f (viewHeigth,viewWidth));
    std::stringstream ss;

view1.setCenter(player.getPosition());

    isLegalMove(*hero,1,-1,first);
    while (window.isOpen()) {
        TileMap map;
        if (!map.load("assets/town.png", sf::Vector2u(16, 16), first, first.getWidth(), first.getHeight()))
            return -1;

        // run the main loop
        while (window.isOpen()) {
            // handle events





          /*  sf::Clock WinTime;
            float Timer = WinTime.getElapsedTime();*/
            bool pause=false;

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
                        if (Happen.key.code == sf::Keyboard::B){
                            if(hero->getPotionNum()!=0)
                            hero->recoverHp(1);}

                        break;
                    case sf::Event::Resized:
                        ResizeView(window,view1);
                        break;
                    default:
                        break;
                }
            }
            sf::sleep((sf::milliseconds(115)));
    bool LeftKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool RightKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool UpKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool DownKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool LShiftKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
    float staminaUsed=0;

    if(LShiftKeyDown){
        if(hero->getStamina()<=0)
            LShiftKeyDown = false;}

    if (LeftKeyDown &&isLegalMove(*hero,-1,0,first)){
        if(LShiftKeyDown&& isLegalMove(*hero,-2,0,first)){
            player.move(-32, 0);
            view1.move(-32,0);
            staminaUsed=1;
            hero->run(-1,0);}else {
            player.move(-16, 0);
            view1.move(-16,0);
            hero->move(-1,0);}}

    if (RightKeyDown&&isLegalMove(*hero,1,0,first) ){
        if(LShiftKeyDown&& isLegalMove(*hero,2,0,first)){
            player.move(32, 0);
            view1.move(32,0);
            staminaUsed=1;
            hero->run(1,0);}else {
            player.move(16, 0);
            view1.move(16,0);
            hero->move(1,0);
        }}

    if (UpKeyDown&&isLegalMove(*hero,0,1,first) ){
        if(LShiftKeyDown&& isLegalMove(*hero,0,2,first)){
            player.move(0, 32);
            view1.move(0,32);
            staminaUsed=1;
            hero->run(0,1);}else{
            player.move(0, 16);
            view1.move(0,16);
            hero->move(0,1);}}

    if (DownKeyDown&&isLegalMove(*hero,0,-1,first) ){
        if(LShiftKeyDown&& isLegalMove(*hero,0,-2,first)){
            player.move(0, -32);
            view1.move(0,-32);
            staminaUsed=1;
            hero->run(0,-1);}else {
            player.move(0, -16);
            view1.move(0,-16);
            hero->move(0,-1);}}



    hero->stamUse(staminaUsed);




            // draw the map
            window.clear();
            view1.setCenter(player.getPosition());
            window.setView(view1);

            window.draw(map);
            window.draw(player);






            //Potion.setColor(sf::Color::Red);


            stamina.setSize(sf::Vector2f (hero->getStamina()/10*16.0f, 7.0f));
            life.setSize(sf::Vector2f (hero->getHp()/10*16.0f, 7.0f));
            life.setPosition(player.getPosition().x-265,player.getPosition().y-150);
            stamina.setPosition(life.getPosition().x,life.getPosition().y+8);
            //stamina.setSize(sf::Vector2f(hero->getStamina()/10*16.0f, 5.0f));//fixme
            Potion.setPosition(int(player.getPosition().x-265), int(player.getPosition().y-137));
            ss << hero->getPotionNum();
            Potion.setString( ss.str().c_str() );

            ss.str("");

            window.draw(life);
            window.draw(stamina);
            window.draw(Potion);
            window.display();
        }


    }
    return 0;
}