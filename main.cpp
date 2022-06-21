#include <iostream>
#include "Tile.h"
#include "Dungeonarea.h"
#include "Mario.h"
//#include "Spawner.h"
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Template.h"
#include "Dice.h"
#include "Obstacle.h"
#include "Item.h"
#include "Boss.h"
#include <string>
#include "Animation.h"
#include <ctime>
//todo texture per stamina e vita e metodi per raccogliere pozioni,sistemare i template in modo che
//todo e che si ignori nemici e boss morti e oggetti raccolti
//todo disegnare i vari oggetti e altri vettori
//todo rendere più veloce l'applicazione

//todo implementare skills con le varie texture(stessa cosa con nemici e boss)
//todo implementare oggetti paesaggio causali(alberi,ceppi,sassi ,pozzi,cartelli.....)
//todo implementare metodi world
//todo implementare audio
static const int viewHeigth = 300;

std::vector<Obstacle*> enemies;
std::vector<Item*> items;
std::vector<Object*> safezones;
std::vector<Object*> teleports;
std::vector<Boss*> bosses;
//static const int width = 1080, length = 1920;
/*enum class GameEvent {
    quit, left, up, down, right, fight, magic, noop
};*/

    void spawn( const int numObstacle, const int numObject, const int numSafezone,
                         const int numBoss,  Dungeonarea &map) {

       enemies.reserve(numObstacle);
        safezones.reserve(numSafezone);
        items.reserve(numObject);
        bosses.reserve(numBoss);
        teleports.reserve(numBoss);

        Dice itemTypeDice(3);
        Dice relPositionDispl(10);
        for(int i=0; i<numObject; i++) {
            Item* item;
            int effect=itemTypeDice.roll(1);
            if(effect==1) {
                item = new Item(1,1,1,"item",1);
            } else if(effect==2) {
                item = new Item(1,1,1,"item",2);
            }else{
                item = new Item(1,1,1,"item",3);
            }

            int flipSearch = 0;
            bool positionFound = false;
            int startX=map.getRand(0,map.getWidth());
            int startY=map.getRand(0,map.getHeight());
            int itemPositionX = startX;
            int itemPositionY = startY;
            while(!positionFound) {
                if (flipSearch%7==0) {
                    itemPositionX = startX+1;
                    itemPositionY = startY+1;
                }
                if(flipSearch%2) {
                    itemPositionX += relPositionDispl.roll(1+flipSearch);
                    itemPositionY += relPositionDispl.roll(1+flipSearch);
                    flipSearch++;
                } else {
                    itemPositionX -= relPositionDispl.roll(1+flipSearch);
                    itemPositionY -= relPositionDispl.roll(1+flipSearch);
                    flipSearch++;
                }
                if( itemPositionX<0 || itemPositionX>map.getWidth())
                    itemPositionX = startX+1;
                if( itemPositionY<0 || itemPositionY>map.getHeight())
                    itemPositionY = startY+1;
                positionFound = findFreeMapTile(itemPositionX, itemPositionY, map,&items,&enemies,&safezones,&bosses);
                if (itemPositionX == startX && itemPositionY == startY)
                    positionFound = false;
            }
            item->setposX(itemPositionX);
            item->setposY(itemPositionY);
            items.push_back(item);
        }

        Dice BossTypeDice(3);
        bool port;
        for(int i=0; i<numBoss; i++) {
            Boss* boss;
            Object* teleport;
            int effect=itemTypeDice.roll(1);
            if(effect==1) {
                boss = new Boss(2,1,2,3,"boss",1);
            } else if(effect==2) {
                boss = new Boss(2,1,2,3,"boss",1);
            }else{
                boss = new Boss(2,1,2,3,"boss",1);
            }

            int flipSearch = 0;
            bool positionFound = false;
            int startX=map.getRand(0,map.getWidth());
            int startY=map.getRand(0,map.getHeight());
            int bossPositionX = startX;
            int bossPositionY = startY;
            while(!positionFound) {
                if (flipSearch%7==0) {
                    bossPositionX = startX+1;
                    bossPositionY = startY+1;
                }
                if(flipSearch%2) {
                    bossPositionX += relPositionDispl.roll(1+flipSearch);
                    bossPositionY += relPositionDispl.roll(1+flipSearch);
                    flipSearch++;
                } else {
                    bossPositionX -= relPositionDispl.roll(1+flipSearch);
                    bossPositionY -= relPositionDispl.roll(1+flipSearch);
                    flipSearch++;
                }
                if( bossPositionX<0 || bossPositionX>map.getWidth())
                    bossPositionX = startX+1;
                if( bossPositionY<0 ||bossPositionY>map.getHeight())
                    bossPositionY = startY+1;
                positionFound = findFreeMapTile(bossPositionX, bossPositionY, map, &items,&enemies,&safezones,&bosses);
                if (bossPositionX == startX && bossPositionY == startY)
                    positionFound = false;
            }
            boss->setposX(bossPositionX);
            boss->setposY(bossPositionY);
            teleport=new Object(0,bossPositionX,bossPositionY,"teleport");
            bosses.push_back(boss);
            teleports.push_back(teleport);
        }

        for(int i=0; i<numSafezone; i++) {
            Object* safezone;
            safezone = new Object(1,2,2,"safezone");
            int flipSearch = 0;
            bool positionFound = false;
            int startX=map.getRand(0,map.getWidth());
            int startY=map.getRand(0,map.getHeight());
            int safezonePositionX = startX;
            int safezonePositionY = startY;
            while(!positionFound) {
                if (flipSearch%7==0) {
                    safezonePositionX = startX+1;
                    safezonePositionY = startY+1;
                }
                if(flipSearch%2) {
                    safezonePositionX += relPositionDispl.roll(1+flipSearch);
                    safezonePositionY += relPositionDispl.roll(1+flipSearch);
                    flipSearch++;
                } else {
                    safezonePositionX -= relPositionDispl.roll(1+flipSearch);
                    safezonePositionY -= relPositionDispl.roll(1+flipSearch);
                    flipSearch++;
                }
                if( safezonePositionX<0 || safezonePositionX>map.getWidth())
                    safezonePositionX = startX+1;
                if( safezonePositionY<0 || safezonePositionY>map.getHeight())
                    safezonePositionY = startY+1;
                positionFound = findFreeMapTile(safezonePositionX, safezonePositionY, map, &items,&enemies,&safezones,&bosses);
                if (safezonePositionX == startX && safezonePositionY == startY)
                    positionFound = false;
                for (auto gc : bosses) {
                    if (l2Distance(*gc,safezonePositionX,safezonePositionY)<30)
                        positionFound = false;}

            }
            safezone->setposX(safezonePositionX);
            safezone->setposY(safezonePositionY);
            safezones.push_back(safezone);
        }
        Dice enemyTypeDice(3);//todo fare in modo che i nemici peggio abbiano meno possibilità

        for(int i=0; i<numObstacle; i++) {
            Obstacle* enemy;
            int effect=itemTypeDice.roll(1);
            if(effect==1) {
                enemy = new Obstacle(5,1,8,2,"enemy",true);
            } else if(effect==2) {
                enemy = new Obstacle(5,1,8,2,"enemy",true);
            }else{
                enemy = new Obstacle(5,1,8,2,"enemy",true);
            }

            int flipSearch = 0;
            bool positionFound = false;
            int startX=map.getRand(0,map.getWidth());
            int startY=map.getRand(0,map.getHeight());
            int enemyPositionX = startX;
            int enemyPositionY = startY;
            while(!positionFound) {
                if (flipSearch%7==0) {
                    enemyPositionX = startX+1;
                    enemyPositionY = startY+1;
                }
                if(flipSearch%2) {
                    enemyPositionX += relPositionDispl.roll(1+flipSearch);
                    enemyPositionY += relPositionDispl.roll(1+flipSearch);
                    flipSearch++;
                } else {
                    enemyPositionX -= relPositionDispl.roll(1+flipSearch);
                    enemyPositionY -= relPositionDispl.roll(1+flipSearch);
                    flipSearch++;
                }
                if( enemyPositionX<0 || enemyPositionX>map.getWidth())
                    enemyPositionX = startX+1;
                if( enemyPositionY<0 ||enemyPositionY>map.getHeight())
                    enemyPositionY = startY+1;
                positionFound = findFreeMapTile(enemyPositionX, enemyPositionY, map, &items,&enemies,&safezones,&bosses);
                if (enemyPositionX == startX && enemyPositionY == startY)
                    positionFound = false;
                for (auto gc : bosses) {
                    if (l2Distance(*gc,enemyPositionX,enemyPositionY)<30)
                        positionFound = false;

                }
                for (auto gc : safezones) {
                    if (l2Distance(*gc,enemyPositionX,enemyPositionY)<15)
                        positionFound = false;

                }
            }
            enemy->setposX(enemyPositionX);
            enemy->setposY(enemyPositionY);
            enemies.push_back(enemy);
        }



    }






void ResizeView(const sf::RenderWindow &window, sf::View &view) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(viewHeigth * aspectRatio, viewHeigth);
}


class TileMap : public sf::Drawable, public sf::Transformable {
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
bool loadTexture(const std::string& tileset){
    if (!m_tileset.loadFromFile(tileset))
        return false;
    return true;
    }
    bool loaditem ( sf::Vector2u tileSize,std::vector<Item*>* item,int numItem,sf::RenderWindow *window)
    {
        // load the tileset texture



        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize( numItem* 4);
        for (auto gc : *item) {
            if(!(gc->isTaken())) {
                int i = 0;
                int tileNumber = 7;
                if (gc->getEffect() == 2) {
                    tileNumber = 3;

                } else if (gc->getEffect() == 3) {
                    tileNumber = 6;

                }
                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad


                // define its 4 corners
                m_vertices[0].position = sf::Vector2f(gc->getposX() * tileSize.x, gc->getposY() * tileSize.y);
                m_vertices[1].position = sf::Vector2f((gc->getposX() + 1) * tileSize.x, gc->getposY() * tileSize.y);
                m_vertices[2].position = sf::Vector2f((gc->getposX() + 1) * tileSize.x,
                                                      (gc->getposY() + 1) * tileSize.y);
                m_vertices[3].position = sf::Vector2f(gc->getposX() * tileSize.x, (gc->getposY() + 1) * tileSize.y);

                // define its 4 texture coordinates
                m_vertices[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                m_vertices[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                m_vertices[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                m_vertices[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                i++;
                window->draw(m_vertices, &m_tileset);
            }}
        // populate the vertex array, with one quad per tile

                // get the current tile number

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
    int monsterNumber;
    int objectNumber;
    int safezoneNumber;
    int bossNumber;
    Dungeonarea first(200, 200, 20, 20, 1, 40, 200, 50, 50);
   spawn(0,10,1,1,first);
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "try",sf::Style::Fullscreen);
    // run the program as long as the window is open
    sf::RectangleShape player(sf::Vector2f(16.0f, 16.0f));

    sf::Texture playerTexture;


    if(!playerTexture.loadFromFile("../assets/mario.png"))
        return -1;//todo funzionante

playerTexture.setSmooth(false);
    player.setTexture(&playerTexture);
    Animation animationPlayer(&playerTexture,sf::Vector2u (4,4),0.2);
    int state;
    bool run=false;
   float deltaTime=0.0f;
   sf::Clock clock;

    window.setFramerateLimit(100);
    Mario* hero;
    int startX = 0;
    int HudXOffset=-265;
    int HudYOffset =-147;
    float HudBarsHeigth=7;
    int startY = 0;
    findFreeMapTile(startX, startY, first,&bosses,&items,&enemies,&safezones);//todo controllare il passaggio dei vettori
    hero = new Mario(100, 1, 0, 0, "prova",40,2);
    sf::RectangleShape life(sf::Vector2f(hero->getHp()/10*16.0f, HudBarsHeigth));
    sf::RectangleShape stamina(sf::Vector2f(hero->getStamina()/10*16.0f, HudBarsHeigth));

    life.setFillColor(sf::Color::Red);
    sf::Font myFont;
    sf::Text Potion;
    Potion.setFont(myFont);
    //hero->setHp(50); per testare la cura
    Potion.setFillColor(sf::Color::White);
    Potion.setCharacterSize(128);
    Potion.setScale(sf::Vector2f(0.1,0.1));
    Potion.setOutlineColor(sf::Color::Black);
    float thickness=1;
    Potion.setOutlineThickness(thickness);




    if (!myFont.loadFromFile("../assets/arial.ttf"))
    {
        return -1;
    }
    stamina.setFillColor(sf::Color::Yellow);
    life.setOutlineColor(sf::Color::Black);
    life.setOutlineThickness(thickness);
    stamina.setOutlineColor(sf::Color::Black);
    stamina.setOutlineThickness(thickness);
    hero->setposX(startX);
    hero->setposY(startY);

    player.setPosition(startX*16,startY*16);

    sf::View view1(sf::Vector2f (0.0f,0.0f),sf::Vector2f (viewHeigth,viewHeigth));
    std::stringstream ss;

    view1.setCenter(player.getPosition());

   // isLegalMove(*hero,1,-1,first);
    while (window.isOpen()) {
        TileMap map,object;
        if (!map.load("../assets/town.png", sf::Vector2u(16, 16), first, first.getWidth(), first.getHeight()))
            return -1;
if(!object.loadTexture("../assets/potions.png"))
    return -1;
        animationPlayer.updatePlayer(deltaTime,run,state);
        player.setTextureRect(animationPlayer.uvRect);

        player.setOrigin(1,7);
        player.setScale(1.2,1.7);

        // run the main loop
        while (window.isOpen()) {
            // handle events
state=0;
       deltaTime=clock.restart().asSeconds();



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
                        if (Happen.key.code == sf::Keyboard::R){
                            for(auto gc:items){
                                if(l2Distance(*gc,hero->getposX(),hero->getposY())<=1){
                                    bool take=sf::Keyboard::isKeyPressed(sf::Keyboard::R);

                                        switch (gc->getEffect()) {
                                            case 1:
                                                hero->setPotionNum(1) ;
                                                break;
                                            case 2:
                                                hero->setMaxHp(hero->getMaxHp()/10);
                                                hero->setHp(hero->getMaxHp());
                                                break;
                                            case 3:
                                                hero->setMaxStam(hero->getMaxStam()/10);

                                                break;
                                        }
                                        gc->setTaken(true);

                                }
                            }}

                        break;
                    /*case sf::Event::Resized:
                        ResizeView(window,view1);
                        break;*/
                    default:
                        break;
                }
            }
            sf::sleep((sf::milliseconds(120)));
    bool LeftKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool RightKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool UpKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool DownKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool LShiftKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
    float staminaUsed=0;
    ResizeView(window,view1);


    if(RightKeyDown||UpKeyDown||DownKeyDown||LeftKeyDown){
        if(LShiftKeyDown){
            if(hero->getStamina()<=0)
                LShiftKeyDown = false;
            bool run=true;
    }
        if(LeftKeyDown){//todo fare corsa
            state=1;}else{
            state=2;
        }
            }


    if (LeftKeyDown &&isLegalMove(*hero,-1,0,first,&bosses,&items,&enemies,&teleports)){
        if(LShiftKeyDown&& isLegalMove(*hero,-2,0,first,&bosses,&items,&enemies,&teleports)){
            player.move(-32, 0);
            view1.move(-32,0);
            staminaUsed=1;
            hero->run(-1,0);}else {
            player.move(-16, 0);
            view1.move(-16,0);
            hero->move(-1,0);}}

    if (RightKeyDown&&isLegalMove(*hero,1,0,first,&bosses,&items,&enemies,&teleports) ){
        if(LShiftKeyDown&& isLegalMove(*hero,2,0,first,&bosses,&items,&enemies,&teleports)){
            player.move(32, 0);
            view1.move(32,0);
            staminaUsed=1;
            hero->run(1,0);}else {
            player.move(16, 0);
            view1.move(16,0);
            hero->move(1,0);
        }}

    if (UpKeyDown&&isLegalMove(*hero,0,1,first,&bosses,&items,&enemies,&teleports) ){
        if(LShiftKeyDown&& isLegalMove(*hero,0,2,first,&bosses,&items,&enemies,&teleports)){
            player.move(0, 32);
            view1.move(0,32);
            staminaUsed=1;
            hero->run(0,1);}else{
            player.move(0, 16);
            view1.move(0,16);
            hero->move(0,1);}}

    if (DownKeyDown&&isLegalMove(*hero,0,-1,first,&bosses,&items,&enemies,&teleports) ){
        if(LShiftKeyDown&& isLegalMove(*hero,0,-2,first,&bosses,&items,&enemies, &teleports)){
            player.move(0, -32);
            view1.move(0,-32);
            staminaUsed=1;
            hero->run(0,-1);}else {
            player.move(0, -16);
            view1.move(0,-16);
            hero->move(0,-1);}}



    hero->stamUse(staminaUsed);
    hero->recoverStam((0.5));


animationPlayer.updatePlayer(deltaTime,run,state);
player.setTextureRect(animationPlayer.uvRect);


            window.clear();
            view1.setCenter(player.getPosition());
            window.setView(view1);

            window.draw(map);
            window.draw(player);









            stamina.setSize(sf::Vector2f (hero->getStamina()/10*16.0f, HudBarsHeigth));
            life.setSize(sf::Vector2f (hero->getHp()/10*16.0f, HudBarsHeigth));
            life.setPosition(player.getPosition().x+HudXOffset,player.getPosition().y+HudYOffset);
            stamina.setPosition(life.getPosition().x,life.getPosition().y+8);
            Potion.setPosition(life.getPosition().x, stamina.getPosition().y+8);
            ss << hero->getPotionNum();
            Potion.setString( ss.str().c_str() );

            ss.str("");
            object.loaditem( sf::Vector2u(16, 16), &items,16,&window);
            window.draw(life);
            window.draw(stamina);
            window.draw(Potion);


          //  window.draw(object);
            window.display();
        }


    }
    return 0;
}