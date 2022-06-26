#include <iostream>
#include "Tile.h"
#include "Dungeonarea.h"
#include "Mario.h"
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Template.h"
#include "Dice.h"
#include <string>
#include "Animation.h"
#include "Obstacle.h"

//#include <ctime>
//#define VERBOSE
//todo settare distanza tra i vari oggetti

//todo ignori nemici e boss morti

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
std::vector<Teleport*> teleports;
std::vector<Boss*> bosses;
//static const int width = 1080, length = 1920;
/*enum class GameEvent {
    quit, left, up, down, right, fight, magic, noop
};*/
void saveVectors(std::string fileName,std::string name,int Bosses,int Items,int Enemies,int Safezones,std::vector<Boss*>* boss = nullptr, std::vector<Item*>* item = nullptr,
                 std::vector<Obstacle*>* enemy = nullptr, std::vector<Object*>* safezone = nullptr,std::vector<Teleport*>* teleport = nullptr){
    std::ofstream out;
    out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    // try {
    out.open(fileName);
    out << name << std::endl;
    out <<Bosses<< std::endl;
    out <<Items<< std::endl;
    out <<Enemies<< std::endl;
    out <<Safezones<< std::endl;
bool fixed=true;
int control=0;
    for(auto gc:*boss){
        out << gc->getHp() << "\n" << gc->getMovements()<< "\n" << gc->getposX()<< "\n" << gc->getposY()<< "\n" << gc->getStatIncrease();
        out << std::endl;
    }
    for(auto gc:*item){
        out << gc->getMovements() << "\n" << gc->getposX()<< "\n" << gc->getposY()<< "\n" << gc->getEffect()<< "\n" << gc->isTaken();
        out << std::endl;
    }
    for(auto gc:*enemy){

        out << gc->getHp() << "\n" << gc->getMovements()<< "\n" << gc->getposX()<< "\n" << gc->getposY()<< "\n" <<gc->isFixed();
        out << std::endl;
    }

    for(auto gc:*safezone){
        out <<gc->getMovements()<< "\n" << gc->getposX()<< "\n" << gc->getposY();
        out << std::endl;
    }

    for(auto gc:*teleport){
        out << gc->getposX()<< "\n" << gc->getposY()<< "\n" << gc->isActivated();
        out << std::endl;
    }
    out.close();
    //}
}
bool loadVectors(std::string fileName,std::string name){
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
        throw GameFileException("Map file is in wrong format", "../vectors/vector.txt", true);
    std::getline(in, fileLine);
    bosses.reserve(std::stoi(fileLine));
    teleports.reserve(std::stoi(fileLine));
    std::getline(in, fileLine);
    items.reserve(std::stoi(fileLine));
    std::getline(in, fileLine);
    enemies.reserve(std::stoi(fileLine));
    std::getline(in, fileLine);
    safezones.reserve(std::stoi(fileLine));
    std::getline(in, fileLine);
    bool fixed=true;
    int control=0;
    try {
    for(auto gc:bosses){
        gc->setHp(std::stoi(fileLine));
        std::getline(in, fileLine);
        gc->setMovements(std::stoi(fileLine));
        std::getline(in, fileLine);
        gc->setposX(std::stoi(fileLine));
        std::getline(in, fileLine);
        gc->setposY(std::stoi(fileLine));
        std::getline(in, fileLine);
        gc->setStatIncrease(std::stoi(fileLine));
        std::getline(in, fileLine);
    }
    for(auto gd:items){
        gd->setMovements(std::stoi(fileLine));
        std::getline(in, fileLine);
        gd->setposX(std::stoi(fileLine));
        std::getline(in, fileLine);
        gd->setposY(std::stoi(fileLine));
        std::getline(in, fileLine);
        gd->setEffect(std::stoi(fileLine));
        std::getline(in, fileLine);
        gd->setTaken(std::stoi(fileLine));
        std::getline(in, fileLine);
    }
    for(auto gb:enemies){
        gb->setHp(std::stoi(fileLine));
        std::getline(in, fileLine);
        gb->setMovements(std::stoi(fileLine));
        std::getline(in, fileLine);
        gb->setposX(std::stoi(fileLine));
        std::getline(in, fileLine);

        gb->setposY(std::stoi(fileLine));
        std::getline(in, fileLine);
        gb->setFixed(std::stoi(fileLine));
        std::getline(in, fileLine);
    }

    for(auto gv:safezones){
        gv->setMovements(std::stoi(fileLine));
        std::getline(in, fileLine);
        gv->setposX(std::stoi(fileLine));
        std::getline(in, fileLine);
        gv->setposY(std::stoi(fileLine));
        std::getline(in, fileLine);

    }

    for(auto gm:teleports){
        gm->setposX(std::stoi(fileLine));
        std::getline(in, fileLine);
        gm->setposY(std::stoi(fileLine));
        std::getline(in, fileLine);
        gm->setActivated(std::stoi(fileLine));
       // std::getline(in, fileLine);
    }
    } catch (std::out_of_range &e) {
        throw std::out_of_range("Can not set vector tile at x: ");
    }




    in.close();
    return true;





}
bool findFreeMapTile(int &x, int &y,const Dungeonarea &map, std::vector<Boss*>* boss = nullptr, std::vector<Item*>* item = nullptr,
                     std::vector<Obstacle*>* enemy = nullptr, std::vector<Object*>* safezone = nullptr) {
    for (int i = x; i < map.getWidth(); i++) {
        for (int j = y; j < map.getHeight(); j++) {
            if (map.getcell(i,j) == TileType::floor) {

                x = i;
                y = j;
                // additional check
if(boss!= nullptr){
    for (auto gb : *boss) {
        if (gb->getposY() == y && gb->getposX() == x)
            return false;
    }
}


                if(item!= nullptr){
                    for (auto gi : *item) {
                        if (gi->getposY() == y && gi->getposX() == x)
                            return false;
                    }}

                if(enemy!= nullptr){
                    for (auto ge : *enemy) {
                        if (ge->getposY() == y && ge->getposX() == x)
                            return false;
                    }}

if(safezone!=nullptr){
                    for (auto gs : *safezone) {
                        if (gs->getposY() == y && gs->getposX() == x)
                            return false;
                    }

                return true;
            }}
        }

    }return false;}
void create(const int numObstacle, const int numObject, const int numSafezone,
            const int numBoss){
    enemies.reserve(numObstacle);
    safezones.reserve(numSafezone);
    items.reserve(numObject);
    bosses.reserve(numBoss);
    teleports.reserve(numBoss);

    Dice itemTypeDice(3);

    for(int i=0; i<numObject; i++) {
        Item* item;
        int effect=itemTypeDice.roll(1);
        if(effect==1) {
            item = new Item(1,1,1,1);
        } else if(effect==2) {
            item = new Item(1,1,1,2);
        }else{
            item = new Item(1,1,1,3);
        }
        items.push_back(item);
    }

    Dice BossTypeDice(3);

    for(int i=0; i<numBoss; i++) {
        Boss* boss;
        Teleport* teleport;
        int effect=BossTypeDice.roll(1);
        if(effect==1) {
            boss = new Boss(2,1,2,2,1);
        } else if(effect==2) {
            boss = new Boss(2,1,2,2,1);
        }else{
            boss = new Boss(2,1,2,2,1);
        }


        teleport=new Teleport(3,3);
        bosses.push_back(boss);
        teleports.push_back(teleport);
    }

    for(int i=0; i<numSafezone; i++) {
        Object* safezone;
        safezone = new Object(1,4,4);


        safezones.push_back(safezone);
    }

    Dice enemyTypeDice(3);//todo fare in modo che i nemici peggio abbiano meno possibilità

    for(int i=0; i<numObstacle; i++) {
        Obstacle* enemy;
        int effect=enemyTypeDice.roll(1);
        if(effect==1) {
            enemy = new Obstacle(5,1,8,2,true);
        } else if(effect==2) {
            enemy = new Obstacle(5,1,8,2,true);
        }else{
            enemy = new Obstacle(5,1,8,2,true);
        }
        enemies.push_back(enemy);
    }
}
template<typename T>

    void spawn(  Dungeonarea &map,T* Vector=nullptr) {

    bool positionFound = false;
    int itemPositionX = 0;
    int itemPositionY = 0;
    TileType control=TileType::Unused;
    for (auto gc: *Vector) {

        positionFound = false;
        std::cout << "# auto \t" ;

        while (true) {
            std::cout << "# while \t" ;
            itemPositionX = 0;
            itemPositionY = 0;
            //control=TileType::Unused;

            itemPositionX = map.getRand(0, (map.getWidth() - 1));
            itemPositionY = map.getRand(0, (map.getHeight() - 1));
            control=map.getcell(itemPositionX, itemPositionY);
            std::cout << "# control \t" ;
            if ( control== TileType::floor) {//fixme
                positionFound = true;



                if (!(bosses.empty())) {
                    for (auto gb: bosses) {
                        if (gb->getposY() == itemPositionY && gb->getposX() == itemPositionX)
                            positionFound = false;
                    }
                }


                if (!(items.empty())) {
                    for (auto gi: items) {
                        if (gi->getposY() == itemPositionY && gi->getposX() == itemPositionX)
                            positionFound = false;
                    }
                }

                if (!(enemies.empty())) {
                    for (auto ge: enemies) {
                        if (ge->getposY() == itemPositionY && ge->getposX() == itemPositionX)
                            positionFound = false;
                    }
                }

                if (!(safezones.empty())) {
                    for (auto gs: safezones) {
                        if (gs->getposY() == itemPositionY && gs->getposX() == itemPositionX)
                            positionFound = false;
                    }


                }

            }

if(positionFound)
    break;
        }gc->setposX(itemPositionX);
        gc->setposY(itemPositionY);


    }
}





void ResizeView(const sf::RenderWindow &window, sf::View &view) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(viewHeigth * aspectRatio, viewHeigth);
}


class TileMap : public sf::Drawable, public sf::Transformable {
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize,const Dungeonarea &map, unsigned int width, unsigned int height)
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

    bool loadTexture(const std::string& tileset){
        if (!m_tileset.loadFromFile(tileset))
            return false;
        return true;
    }


    template<typename T>
    bool loaditem ( sf::Vector2u tileSize, int numItem,sf::RenderWindow *window,T *item=nullptr)
    {



        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize( numItem* 4);
        int tileNumber=0;
        int tv=0;
        int tu=0;
        int i=0;

        for (auto gl : *item) {

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

    template<typename T>
    bool loadTeleport ( sf::Vector2u tileSize, int numItem,sf::RenderWindow *window,T *item=nullptr)
    {



        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize( numItem* 4);
        int tileNumber=0;
        int tv=0;
        int tu=0;
        int i=0;

        for (auto gl : *item) {

             if(gl->isActivated()) {

                tileNumber = 11*13;

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
        }
        return true;
    }

    template<typename T>
    bool loadSafezone ( sf::Vector2u tileSize, int numItem,sf::RenderWindow *window,T *item=nullptr)
    {



        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize( numItem* 4);
        int tileNumber=0;
        int tv=0;
        int tu=0;
        int i=0;

        for (auto gl : *item) {



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
    int monsterNumber=5;
    int objectNumber=15;
    int safezoneNumber=8;
    int bossNumber=8;
    int numberMap=6;
    int mapIndex=0;
    std::string saves[6]={
            "../map/1.txt",
            "../map/2.txt",
            "../map/3.txt",
            "../map/4.txt",
            "../map/5.txt",
            "../map/6.txt",

    };
    std::string savesVec[6]={
            "../vectors/1v.txt",
            "../vectors/2v.txt",
            "../vectors/3v.txt",
            "../vectors/4v.txt",
            "../vectors/5v.txt",
            "../vectors/6v.txt",

    };
    std::string names[6]={
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
    };
    Dungeonarea *maps[numberMap];


    try {
    long oldseed=0;
    //todo salvataggio e caricamento vettori vari e stato mario
        for(int i=0;i<numberMap;i++){
            maps[i]=new Dungeonarea(oldseed,250, 250, 20, 20, 1, 40, 200, 100, 100,names[i],saves[i]);

       if(!maps[i]->loadMap(saves[i],names[i])){


           oldseed=maps[i]->getOldseed();
           maps[i]->saveMap(saves[i]);}
       }
    } catch(GameFileException& e) {
        std::cerr << e.what() << std::endl;
        e.printError();
        if(e.isFatal())
            abort();
    } catch(std::runtime_error& e) {
        std::cerr << "std::runtime_error" << std::endl;
        std::cerr << e.what() << std::endl;
        abort();
    } catch(std::out_of_range& e) {
        std::cerr << "std::out_of_range" << std::endl;
        std::cerr << e.what() << std::endl;
        abort();
    }


    std::cout << "# of tiles made: \t" ;
    create(monsterNumber,objectNumber,safezoneNumber,bossNumber);
   /* long oldseed2=0;//fixme salvataggio e caricamento vettori
    for(int i=0;i<numberMap;i++) {
        maps[i]->setOldseed(oldseed2);
        create(monsterNumber,objectNumber,safezoneNumber,bossNumber);
        if (!loadVectors(savesVec[i],names[i])) {
            std::cout << "# of tiles made: \t" ;
            spawn( *maps[i],&items);
            std::cout << "# of tiles made: \t" ;
            spawn(*maps[i],&bosses);
            spawn(*maps[i],&teleports);
            std::cout << "# of tiles made: \t" ;
            spawn(*maps[i],&safezones);
            std::cout << "# of tiles made: \t" ;
            spawn(*maps[i],&enemies);
            std::cout << "# of tiles made: \t" ;

            saveVectors(savesVec[i],names[i],bossNumber, objectNumber, monsterNumber, safezoneNumber, &bosses, &items, &enemies, &safezones,
                        &teleports);
        }
    }*/

    std::cout << "# of tiles made: \t" ;
   spawn( *maps[mapIndex],&items);
    std::cout << "# of tiles made: \t" ;
    spawn(*maps[mapIndex],&bosses);
    spawn(*maps[mapIndex],&teleports);
    std::cout << "# of tiles made: \t" ;
    spawn(*maps[mapIndex],&safezones);
    std::cout << "# of tiles made: \t" ;
    spawn(*maps[mapIndex],&enemies);
    std::cout << "# of tiles made: \t" ;

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "try",sf::Style::Fullscreen);
    window.setFramerateLimit(100);


    sf::RectangleShape player(sf::Vector2f(16.0f, 16.0f));
    sf::Texture playerTexture;

    if(!playerTexture.loadFromFile("../assets/mario.png"))
        return -1;

    playerTexture.setSmooth(false);
    player.setTexture(&playerTexture);
    Animation animationPlayer(&playerTexture,sf::Vector2u (4,4),0.2);


    int startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 1));
    int startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 1));
    int HudXOffset=-268;
    int HudYOffset =-147;
    int HudBarsHeigth=14;

    while(!(findFreeMapTile(startX, startY, *maps[mapIndex],&bosses,&items,&enemies,&safezones))){
        startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 1));
        startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 1));
    }

    Mario* hero;
    hero = new Mario(100, 1, 0, 0,40,2);
    hero->setHp(50);
    hero->setposX(startX);
    hero->setposY(startY);
    player.setPosition(startX*16,startY*16);
    player.setOrigin(1,7);
    player.setScale(1.2,1.7);


    sf::View view1(sf::Vector2f (0.0f,0.0f),sf::Vector2f (viewHeigth,viewHeigth));
    view1.setCenter(player.getPosition());

    sf::RectangleShape life(sf::Vector2f(hero->getHp()/10*16.0f, HudBarsHeigth));
    sf::RectangleShape stamina(sf::Vector2f(hero->getStamina()/10*16.0f, HudBarsHeigth));
    sf::RectangleShape potionIcon(sf::Vector2f(16.0f, 16.0f));
    sf::Texture hpBar,staminaBar,potion;

    if(!hpBar.loadFromFile("../assets/hpBar.png"))
        return -1;
    if(!staminaBar.loadFromFile("../assets/green.png"))
        return -1;
    if(!potion.loadFromFile("../assets/potions.png"))
        return -1;
    staminaBar.setSmooth(true);
    hpBar.setSmooth(true);

    life.setTexture(&hpBar);
    stamina.setTexture(&staminaBar);
    potionIcon.setTexture(&potion);

    sf::Vector2u textureSize=potion.getSize();
    textureSize.x/=21;
    textureSize.y/=15;
    potionIcon.setTextureRect(sf::IntRect(textureSize.x*12,textureSize.y*0,textureSize.x,textureSize.y));

    sf::Font myFont;
    sf::Text Potion;
    Potion.setFont(myFont);

    Potion.setFillColor(sf::Color::White);
    Potion.setCharacterSize(128);
    Potion.setScale(sf::Vector2f(0.1,0.1));
    Potion.setOutlineColor(sf::Color::Black);
    int thickness=1;
    Potion.setOutlineThickness(thickness);

    if (!myFont.loadFromFile("../assets/arial.ttf"))
    {
        return -1;
    }

    TileMap map,object,teleport,safezone;

    if (!map.load("../assets/town.png", sf::Vector2u(16, 16), *maps[mapIndex], maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight()))
        return -1;

    if(!object.loadTexture("../assets/potions.png"))
        return -1;
     if(!teleport.loadTexture("../assets/books.png"))
        return -1;
       if(!safezone.loadTexture("../assets/pixelSet.png"))
        return -1;

    object.loaditem( sf::Vector2u(16, 16),objectNumber,&window,&items);
    teleport.loadTeleport( sf::Vector2u(16, 16),bossNumber,&window,&teleports);
    safezone.loadSafezone( sf::Vector2u(16, 16),safezoneNumber,&window,&safezones);

    sf::Clock clock;
    float deltaTime=0.0f;


    int state=0;
    bool run=false;
    float staminaUsed=0;

    std::stringstream ss;

    while (window.isOpen()) {


        while (window.isOpen()) {

            ResizeView(window,view1);
            deltaTime=clock.restart().asSeconds();



            sf::Event Happen;
            while (window.pollEvent(Happen))
            {
                switch (Happen.type){

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

                    case sf::Event::KeyReleased:
                        if (Happen.key.code == sf::Keyboard::R){
                            for(auto gc:items){
                                if(l2Distance(*gc,hero->getposX(),hero->getposY())<=1&&!(gc->isTaken())){


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

                                            default:
                                                break;
                                        }
                                        gc->setTaken(true);
                                    object.loaditem( sf::Vector2u(16, 16),objectNumber,&window,&items);

                                }}}
                        if (Happen.key.code == sf::Keyboard::T){
                            for(auto gc:safezones){
                                if(l2Distance(*gc,hero->getposX(),hero->getposY())<=1){


                                        hero->recoverHp(0);

                                }}}
                        break;

                    default:
                        break;
                }}

            sf::sleep((sf::milliseconds(120)));

            bool LeftKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::A);
            bool RightKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::D);
            bool UpKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
            bool DownKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::W);
            bool LShiftKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

            staminaUsed=0;
            state=0;
            run=false;



            if(RightKeyDown||UpKeyDown||DownKeyDown||LeftKeyDown){

                if(LShiftKeyDown){
                    if(hero->getStamina()<=0)
                        LShiftKeyDown = false;
                        run=true;}

                if(LeftKeyDown){
                    state=1;
                }else{
                    state=2;}
            }


            if (LeftKeyDown &&isLegalMove(*hero,-1,0,*maps[mapIndex],&bosses,&items,&enemies,&teleports)){

                if(LShiftKeyDown&& isLegalMove(*hero,-2,0,*maps[mapIndex],&bosses,&items,&enemies,&teleports)){
                    player.move(-32, 0);
                    view1.move(-32,0);
                    staminaUsed=1;
                    hero->run(-1,0);
                }else {
                    player.move(-16, 0);
                    view1.move(-16,0);
                    hero->move(-1,0);}}

            if (RightKeyDown&&isLegalMove(*hero,1,0,*maps[mapIndex],&bosses,&items,&enemies,&teleports) ){
                if(LShiftKeyDown&& isLegalMove(*hero,2,0,*maps[mapIndex],&bosses,&items,&enemies,&teleports)){
                    player.move(32, 0);
                    view1.move(32,0);
                    staminaUsed=1;
                    hero->run(1,0);
                }else {
                    player.move(16, 0);
                    view1.move(16,0);
                    hero->move(1,0);}}

            if (UpKeyDown&&isLegalMove(*hero,0,1,*maps[mapIndex],&bosses,&items,&enemies,&teleports) ){
                if(LShiftKeyDown&& isLegalMove(*hero,0,2,*maps[mapIndex],&bosses,&items,&enemies,&teleports)){
                    player.move(0, 32);
                    view1.move(0,32);
                    staminaUsed=1;
                    hero->run(0,1);
                }else{
                    player.move(0, 16);
                    view1.move(0,16);
                    hero->move(0,1);}}

            if (DownKeyDown&&isLegalMove(*hero,0,-1,*maps[mapIndex],&bosses,&items,&enemies,&teleports) ){
                if(LShiftKeyDown&& isLegalMove(*hero,0,-2,*maps[mapIndex],&bosses,&items,&enemies, &teleports)){
                    player.move(0, -32);
                    view1.move(0,-32);
                    staminaUsed=1;
                    hero->run(0,-1);
                }else {
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
            window.draw(teleport);
            window.draw(player);
            window.draw(safezone);
            stamina.setSize(sf::Vector2f (hero->getStamina()/10*16.0f, HudBarsHeigth));
            life.setSize(sf::Vector2f (hero->getHp()/10*16.0f, HudBarsHeigth));

            ss << hero->getPotionNum();
            Potion.setString( ss.str().c_str() );
            ss.str("");

            life.setPosition(player.getPosition().x+HudXOffset,player.getPosition().y+HudYOffset);
            stamina.setPosition(life.getPosition().x+2,life.getPosition().y+8);
            Potion.setPosition(life.getPosition().x+3, stamina.getPosition().y+8);
            potionIcon.setPosition(Potion.getPosition().x+7, Potion.getPosition().y);






            window.draw(life);
            window.draw(stamina);
            window.draw(Potion);
            window.draw(potionIcon);
            window.draw(object);

            window.display();
        }}
    return 0;
}