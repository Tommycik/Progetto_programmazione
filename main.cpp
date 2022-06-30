#include <iostream>
#include "Tile.h"
#include "Dungeonarea.h"
#include "Mario.h"
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Template.h"
#include "World.h"
#include <string>
#include "Animation.h"
#include "Obstacle.h"
#include "Spawner.h"
#include "Textviewer.h"
#include <cstdio>
#include "Loader.h"

//#define VERBOSE
//todo aggiungere cancellazione salvataggi dal gioco
//todo cambiare texture portale
//todo ignori nemici e boss morti
//todo risolvere inaffidabilità spawn a distanza

//todo rendere più veloce l'applicazione

//todo implementare skills con le varie texture(stessa cosa con nemici e boss)
//todo implementare oggetti paesaggio causali(alberi,ceppi,sassi ,pozzi,cartelli.....)
//todo implementare metodi world
//todo implementare audio
static const int viewHeigth = 300;

//todo portare i save in world
void saveVectors(std::string fileName,std::string name,int Bosses,int Items,int Enemies,int Safezones,std::vector<Boss*>* boss = nullptr, std::vector<Item*>* item = nullptr,
                 std::vector<Obstacle*>* enemy = nullptr, std::vector<Object*>* safezone = nullptr,std::vector<Teleport*>* teleport = nullptr){
    std::ofstream out;
    out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    // try {
    out.open(fileName,std::ios_base::trunc);
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
    out << std::endl;
    out.close();
    //}
}
bool loadVectors(std::string fileName,std::string name,Spawner &creator){
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
    creator.getBosses().reserve(std::stoi(fileLine));
    creator.getTeleports().reserve(std::stoi(fileLine));
    std::getline(in, fileLine);
    creator.getItems().reserve(std::stoi(fileLine));
    std::getline(in, fileLine);
    creator.getEnemies().reserve(std::stoi(fileLine));
    std::getline(in, fileLine);
    creator.getSafezones().reserve(std::stoi(fileLine));
    std::getline(in, fileLine);
    bool fixed=true;
    int control=0;
    try {
    for(auto gc:creator.getBosses()){
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
    for(auto gd:creator.getItems()){
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
    for(auto gb:creator.getEnemies()){
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

    for(auto gv:creator.getSafezones()){
        gv->setMovements(std::stoi(fileLine));
        std::getline(in, fileLine);
        gv->setposX(std::stoi(fileLine));
        std::getline(in, fileLine);
        gv->setposY(std::stoi(fileLine));
        std::getline(in, fileLine);

    }

    for(auto gm:creator.getTeleports()){
        gm->setposX(std::stoi(fileLine));
        std::getline(in, fileLine);
        gm->setposY(std::stoi(fileLine));
        std::getline(in, fileLine);
        gm->setActivated(std::stoi(fileLine));
        std::getline(in, fileLine);
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




void ResizeView(const sf::RenderWindow &window, sf::View &view) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(viewHeigth * aspectRatio, viewHeigth);
}




int main() {

    int monsterNumber=5;
    int objectNumber=15;
    int safezoneNumber=3;
    int bossNumber=2;
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

    bool recreate=false;

    try {
    long oldseed=0;


        for(int i=0;i<numberMap;i++){
            maps[i]=new Dungeonarea(oldseed,250, 250, 20, 20, 1, 40, 200, 100, 100,names[i],saves[i]);

       if(!maps[i]->loadMap(saves[i],names[i])){
           recreate=true;

          // remove(*savesVec[i]);
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
    //create(monsterNumber,objectNumber,safezoneNumber,bossNumber);
   long oldseed2=0;

    Spawner *vectors[numberMap];
    for(int i=0;i<numberMap;i++) {
        //maps[i]->setOldseed(oldseed2);
        vectors[i]=new Spawner(monsterNumber,objectNumber,safezoneNumber,bossNumber);
        //vectors[i]->create();
        if ((!loadVectors(savesVec[i],names[i],*vectors[i]))||recreate) {
            recreate=true;
            std::cout << "# of tiles made: \t" ;
            vectors[i]->spawn( *maps[i],&vectors[i]->getItems());
            std::cout << "# of tiles made: \t" ;
            vectors[i]->spawn(*maps[i],&vectors[i]->getBosses());
            vectors[i]->spawn(*maps[i],&vectors[i]->getTeleports());
            std::cout << "# of tiles made: \t" ;
            vectors[i]->spawn(*maps[i],&vectors[i]->getSafezones());
            std::cout << "# of tiles made: \t" ;
            vectors[i]->spawn(*maps[i],&vectors[i]->getEnemies());
            std::cout << "# of tiles made: \t" ;

            saveVectors(savesVec[i],names[i],bossNumber, objectNumber, monsterNumber, safezoneNumber, &vectors[i]->getBosses(), &vectors[i]->getItems(), &vectors[i]->getEnemies(), &vectors[i]->getSafezones(),
                        &vectors[i]->getTeleports());
        }
    }



    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "try",sf::Style::Fullscreen);
    window.setFramerateLimit(100);


    sf::RectangleShape player(sf::Vector2f(16.0f, 16.0f));
    sf::Texture playerTexture;

    if(!playerTexture.loadFromFile("../assets/mario.png"))
        return -1;

    playerTexture.setSmooth(false);
    player.setTexture(&playerTexture);
    Animation animationPlayer(&playerTexture,sf::Vector2u (4,4),0.2);

World game;
    bool tutorialItem=false,tutorialSafezone=false,tutorialTeleport=false;
    Mario* hero;
    hero = new Mario(100, 1, 0, 0,40,2);
if(!game.loadPlayer(mapIndex,*hero,tutorialItem,tutorialSafezone,tutorialTeleport)) {
    recreate= true;

}
if(recreate){
    int startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 1));
    int startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 1));
    while(!(findFreeMapTile(startX, startY, *maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getSafezones()))){
        startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 1));
        startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 1));
    }
    hero->setposX(startX);
    hero->setposY(startY);
}

    int HudXOffset=-268;
    int HudYOffset =-147;
    int HudBarsHeigth=14;




    //hero->setHp(50);

    player.setPosition(hero->getposX()*16,hero->getposY()*16);
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
     if(!teleport.loadTexture("../assets/books.png"))//todo deve diventare calpestabile
        return -1;
       if(!safezone.loadTexture("../assets/pixelSet.png"))
        return -1;

    object.loaditem( sf::Vector2u(16, 16),objectNumber,&window,*vectors[mapIndex]);
    teleport.loadTeleport( sf::Vector2u(16, 16),bossNumber,&window,*vectors[mapIndex]);
    safezone.loadSafezone( sf::Vector2u(16, 16),safezoneNumber,&window,*vectors[mapIndex]);

    sf::Clock clock;
    float deltaTime=0.0f;


    int state=0;
    bool run=false;
    float staminaUsed=0;

    std::stringstream ss;
    Textviewer objectInteraction(window.getSize().y/5,window.getSize().x,128);
    //auto po=vectors[mapIndex]->getTeleports();
    sf::RectangleShape box;
    box.setSize(sf::Vector2f (viewHeigth,viewHeigth/6));
    //fixme 1 è un segnaposto fare in modo che la box nera

    sf::Color color(0,0,0,128);
    box.setFillColor(color);
    box.setOutlineColor(sf::Color::White);

    box.setOutlineThickness(1);

    bool makeText=false,teleportText=false,itemText=false,safezoneText=false;

    while (window.isOpen()) {


        while (window.isOpen()) {

            makeText=false;
            teleportText=false;
            itemText=false;

            for(auto gc:vectors[mapIndex]->getTeleports()){
                if(l2Distance(*gc,hero->getposX(),hero->getposY())<=1&&(gc->isActivated())) {
                makeText=true;
                teleportText=true;}
            }

            if(!tutorialItem){
                for(auto gc:vectors[mapIndex]->getItems()){
                    if(l2Distance(*gc,hero->getposX(),hero->getposY())<=1&&(!gc->isTaken())) {
                        makeText=true;
                        itemText=true;}
                }
            }

            if(!tutorialSafezone){
                for(auto gc:vectors[mapIndex]->getSafezones()){
                    if(l2Distance(*gc,hero->getposX(),hero->getposY())<=1) {
                        makeText=true;
                        safezoneText=true;}
                }
            }




            ResizeView(window,view1);
            deltaTime=clock.restart().asSeconds();



            sf::Event Happen;
            while (window.pollEvent(Happen))
            {
                switch (Happen.type){

                   /* case sf::Event::Closed:
                        window.close();
                        break;*/

                    case sf::Event::KeyPressed:
                        if (Happen.key.code == sf::Keyboard::Escape){
                            game.savePlayer(mapIndex,*hero,tutorialItem,tutorialSafezone,tutorialTeleport);
                            for(int i=0;i<numberMap;i++) {
                                    saveVectors(savesVec[i],names[i],bossNumber, objectNumber, monsterNumber, safezoneNumber, &vectors[i]->getBosses(), &vectors[i]->getItems(), &vectors[i]->getEnemies(), &vectors[i]->getSafezones(),
                                                &vectors[i]->getTeleports());
                                }


                            window.close();
                        }

                        if (Happen.key.code == sf::Keyboard::B){
                            if(hero->getPotionNum()!=0)
                            hero->recoverHp(1);}
                        break;

                    case sf::Event::KeyReleased:
                        if (Happen.key.code == sf::Keyboard::R){
                            for(auto gc:vectors[mapIndex]->getItems()){
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
                                    object.loaditem( sf::Vector2u(16, 16),objectNumber,&window,*vectors[mapIndex]);
                                    tutorialItem=true;
                                }}}
                        if (Happen.key.code == sf::Keyboard::T){
                            for(auto gc:vectors[mapIndex]->getSafezones()){
                                if(l2Distance(*gc,hero->getposX(),hero->getposY())<=1){


                                        hero->recoverHp(0);

                                    tutorialSafezone=true;}}}
                        if (Happen.key.code == sf::Keyboard::O||Happen.key.code == sf::Keyboard::P){
                            for(auto gc:vectors[mapIndex]->getTeleports()){
                                if(l2Distance(*gc,hero->getposX(),hero->getposY())<=1&&gc->isActivated()){//fixme li stampa sotto la mappa dato che è prima;

                            if (Happen.key.code == sf::Keyboard::O){
                                if(mapIndex==numberMap-1) {
                                    mapIndex=0;
                                }else{
                                mapIndex++;}
                            }else if (Happen.key.code == sf::Keyboard::P){
                                if(mapIndex==0) {
                                    mapIndex=numberMap-1;
                                }else{
                                    mapIndex--;}
                            }

                            if (!map.load("../assets/town.png", sf::Vector2u(16, 16), *maps[mapIndex], maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight()))
                                return -1;

                            object.loaditem( sf::Vector2u(16, 16),objectNumber,&window,*vectors[mapIndex]);
                            teleport.loadTeleport( sf::Vector2u(16, 16),bossNumber,&window,*vectors[mapIndex]);
                            safezone.loadSafezone( sf::Vector2u(16, 16),safezoneNumber,&window,*vectors[mapIndex]);


                                    hero->setposX(vectors[mapIndex]->getTeleports()[0]->getposX());//todo risolvere bug creazione teleport,dopo il primo sono solo in posizione 1 1
                                    hero->setposY(vectors[mapIndex]->getTeleports()[0]->getposY());
                                    player.setPosition(hero->getposX()*16,hero->getposY()*16);
                                    tutorialTeleport=true;
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


            if (LeftKeyDown &&isLegalMove(*hero,-1,0,*maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getTeleports())){

                if(LShiftKeyDown&& isLegalMove(*hero,-2,0,*maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getTeleports())){
                    player.move(-32, 0);
                    view1.move(-32,0);
                    staminaUsed=1;
                    hero->run(-1,0);
                }else {
                    player.move(-16, 0);
                    view1.move(-16,0);
                    hero->move(-1,0);}}

            if (RightKeyDown&&isLegalMove(*hero,1,0,*maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getTeleports()) ){
                if(LShiftKeyDown&& isLegalMove(*hero,2,0,*maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getTeleports())){
                    player.move(32, 0);
                    view1.move(32,0);
                    staminaUsed=1;
                    hero->run(1,0);
                }else {
                    player.move(16, 0);
                    view1.move(16,0);
                    hero->move(1,0);}}

            if (UpKeyDown&&isLegalMove(*hero,0,1,*maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getTeleports()) ){
                if(LShiftKeyDown&& isLegalMove(*hero,0,2,*maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getTeleports())){
                    player.move(0, 32);
                    view1.move(0,32);
                    staminaUsed=1;
                    hero->run(0,1);
                }else{
                    player.move(0, 16);
                    view1.move(0,16);
                    hero->move(0,1);}}

            if (DownKeyDown&&isLegalMove(*hero,0,-1,*maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getTeleports()) ){
                if(LShiftKeyDown&& isLegalMove(*hero,0,-2,*maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(), &vectors[mapIndex]->getTeleports())){
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
            box.setPosition(view1.getCenter().x-(view1.getSize().x/4),view1.getCenter().y+(view1.getSize().y/6));
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
            if(hero->getPotionNum()<10){
                potionIcon.setPosition(Potion.getPosition().x+7, Potion.getPosition().y);
            }else{
                potionIcon.setPosition(Potion.getPosition().x+14, Potion.getPosition().y);
            }







            window.draw(life);
            window.draw(stamina);
            window.draw(Potion);
            window.draw(potionIcon);
            window.draw(object);
            if(makeText) {
                window.draw(box);
                if(teleportText){
                    if(tutorialTeleport){

                        objectInteraction.blackBox(box.getPosition().x,box.getPosition().y,"Il teletrasporto emana un'aura misteriosa...","",&window);

                    }else {
                        objectInteraction.blackBox(box.getPosition().x,box.getPosition().y,"Per usare il potere del teletrasporto premere P o O","",&window);//P scorre in avanti mentre  O scorre indietro
                    }


                }
                if(itemText){
                    if(tutorialItem==false){

                        objectInteraction.blackBox(box.getPosition().x,box.getPosition().y,"Per raccogliere gli oggetti premi R","Per usare le pozioni premi B",&window);

                    }
                }
                if(safezoneText){
                    if(tutorialSafezone==false){

                        objectInteraction.blackBox(box.getPosition().x,box.getPosition().y,"Hai trovato una fonte di luce","Per usarne il potere premi T",&window);

                    }
                }
            }
            window.display();
        }}
    for(int i=0;i<numberMap;i++){
        delete maps[i];
        delete vectors[i];
    }

    delete hero;
    return 0;
}