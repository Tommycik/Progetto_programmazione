#include <iostream>
#include "Tile.h"
#include "Dungeonarea.h"
#include "Mario.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Template.h"
#include "World.h"
#include <string>
#include "Animation.h"
#include "Obstacle.h"
#include "Spawner.h"
#include "Textviewer.h"
#include "Loader.h"
#include"Menu.h"
//#define VERBOSE



//fixme tile per non dare errore 0.fffffffff


//todo ignori nemici e boss morti

//todo portare hud su hud


//todo implementare skills con le varie texture(stessa cosa con nemici e boss)
//todo implementare oggetti paesaggio causali(alberi,ceppi,sassi ,pozzi,cartelli.....)


static const int viewHeigth = 300;







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
    float tilesetResolution=16;
    int mapIndex=0;
    std::string saves[6]={
            "map/1.txt",
            "map/2.txt",
            "map/3.txt",
            "map/4.txt",
            "map/5.txt",
            "map/6.txt",

    };
    std::string savesVec[6]={
            "vectors/1v.txt",
            "vectors/2v.txt",
            "vectors/3v.txt",
            "vectors/4v.txt",
            "vectors/5v.txt",
            "vectors/6v.txt",

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


    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "try",sf::Style::Fullscreen);
    window.setFramerateLimit(100);



    sf::Music Game;
    if (!Game.openFromFile("assets/gioco.wav"))
        return -1; // error

    Game.setVolume(50.f);
    Game.setLoop(true);


    Menu menu(&window);

    if(!(menu.load()))
        return false;

    menu.show(&window,numberMap,&saves[0],&savesVec[0]);



    Game.play();

    bool playerReboot=false;
    long oldseed=0;
    try {

        for(int i=0;i<numberMap;i++){
            maps[i]=new Dungeonarea(oldseed,250, 250, 20, 20, i, 40, 200, 100, 100,names[i],saves[i]);

       if(!maps[i]->loadMap(saves[i],names[i])){


          remove(savesVec[i].c_str());
          playerReboot=true;
          oldseed=maps[i]->getOldseed();
          maps[i]->saveMap(saves[i]);}
       }
        if(playerReboot)
        remove("playerSave/save.txt");

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






    Spawner *vectors[numberMap];
    for(int i=0;i<numberMap;i++) {
        vectors[i]=new Spawner(monsterNumber,objectNumber,safezoneNumber,bossNumber);
        if ((!vectors[i]->loadVectors(savesVec[i],names[i]))) {


            vectors[i]->spawn( *maps[i],&vectors[i]->getItems());

            vectors[i]->spawn(*maps[i],&vectors[i]->getBosses());
            vectors[i]->spawn(*maps[i],&vectors[i]->getTeleports());

            vectors[i]->spawn(*maps[i],&vectors[i]->getSafezones());

            vectors[i]->spawn(*maps[i],&vectors[i]->getEnemies());


            vectors[i]->saveVectors(savesVec[i],names[i],bossNumber, objectNumber, monsterNumber, safezoneNumber);
        }
    }






    sf::RectangleShape player(sf::Vector2f(tilesetResolution, tilesetResolution));
    sf::Texture playerTexture;

    if(!playerTexture.loadFromFile("assets/mario.png"))
        return -1;

    playerTexture.setSmooth(false);
    player.setTexture(&playerTexture);
    Animation animationPlayer(&playerTexture,sf::Vector2u (4,4),0.2);

    World game;
    bool tutorialItem=false,tutorialSafezone=false,tutorialTeleport=false;
    Mario* hero;
    hero = new Mario(100, 1, 0, 0,40,2);
    if(!game.loadPlayer(mapIndex,*hero,tutorialItem,tutorialSafezone,tutorialTeleport)) {

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

    player.setPosition(hero->getposX()*16,hero->getposY()*16);//todo levare 16 magic number
    player.setOrigin(1,7);
    player.setScale(1.2,1.7);


    sf::View view1(sf::Vector2f (0.0f,0.0f),sf::Vector2f (viewHeigth,viewHeigth));
    view1.setCenter(player.getPosition());

    sf::RectangleShape life(sf::Vector2f(hero->getHp()/10*tilesetResolution, HudBarsHeigth));
    sf::RectangleShape stamina(sf::Vector2f(hero->getStamina()/10*tilesetResolution, HudBarsHeigth));
    sf::RectangleShape potionIcon(sf::Vector2f(tilesetResolution, tilesetResolution));
    sf::Texture hpBar,staminaBar,potion;

    if(!hpBar.loadFromFile("assets/hpBar.png"))
        return -1;
    if(!staminaBar.loadFromFile("assets/green.png"))
        return -1;
    if(!potion.loadFromFile("assets/potions.png"))
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

    if (!myFont.loadFromFile("assets/arial.ttf"))
    {
        return -1;
    }

    TileMap map,object,teleport,safezone;

    if (!map.load("assets/Textures-16.png", sf::Vector2u(tilesetResolution, tilesetResolution), *maps[mapIndex], maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight()))
        return -1;

    if(!object.loadTexture("assets/potions.png"))
        return -1;
     if(!teleport.loadTexture("assets/portalRings1.png"))
        return -1;
       if(!safezone.loadTexture("assets/pixelSet.png"))
        return -1;

    object.loaditem( sf::Vector2u(tilesetResolution, tilesetResolution),objectNumber,&window,*vectors[mapIndex]);
    teleport.loadTeleport( sf::Vector2u(tilesetResolution, tilesetResolution),bossNumber,&window,*vectors[mapIndex]);
    safezone.loadSafezone( sf::Vector2u(tilesetResolution, tilesetResolution),safezoneNumber,*vectors[mapIndex]);



    int state=0;
    bool run=false;
    float staminaUsed=0;

    std::stringstream ss;
    Textviewer objectInteraction(window.getSize().y/5,window.getSize().x,128);


    sf::RectangleShape box;
    box.setSize(sf::Vector2f (viewHeigth,viewHeigth/6));


    sf::Color color(0,0,0,128);
    box.setFillColor(color);
    box.setOutlineColor(sf::Color::White);

    box.setOutlineThickness(1);

    bool makeText=false,teleportText=false,itemText=false,safezoneText=false;



    sf::Clock clock;
    float deltaTime=0.0f;
    while (window.isOpen()) {


        while (window.isOpen()) {


            teleportText=false;
            itemText=false;
            makeText=objectInteraction.checker(*vectors[mapIndex],*hero,itemText,safezoneText,teleportText,tutorialSafezone,
                                               tutorialItem);






            deltaTime=clock.restart().asSeconds();

            ResizeView(window,view1);


            sf::Event Happen;
            while (window.pollEvent(Happen))
            {
                switch (Happen.type){

                    case sf::Event::Closed:
                        window.close();
                        break;




                    case sf::Event::KeyPressed:
                        if (Happen.key.code == sf::Keyboard::Escape){
                            game.savePlayer(mapIndex,*hero,tutorialItem,tutorialSafezone,tutorialTeleport);
                            for(int i=0;i<numberMap;i++) {
                                    vectors[i]->saveVectors(savesVec[i],names[i],bossNumber, objectNumber, monsterNumber, safezoneNumber);
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
                                    object.loaditem( sf::Vector2u(tilesetResolution, tilesetResolution),objectNumber,&window,*vectors[mapIndex]);
                                    tutorialItem=true;
                                }}}
                        if (Happen.key.code == sf::Keyboard::T){
                            for(auto gc:vectors[mapIndex]->getSafezones()){
                                if(l2Distance(*gc,hero->getposX(),hero->getposY())<=1){


                                        hero->recoverHp(0);

                                    tutorialSafezone=true;}}}
                        if (Happen.key.code == sf::Keyboard::O||Happen.key.code == sf::Keyboard::P){
                            for(auto gc:vectors[mapIndex]->getTeleports()){
                                if(l2Distance(*gc,hero->getposX(),hero->getposY())<=1&&gc->isActivated()){

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

                            if (!map.load("assets/Textures-16.png", sf::Vector2u(tilesetResolution, tilesetResolution), *maps[mapIndex], maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight()))
                                return -1;

                            object.loaditem( sf::Vector2u(tilesetResolution, tilesetResolution),objectNumber,&window,*vectors[mapIndex]);
                            teleport.loadTeleport( sf::Vector2u(tilesetResolution, tilesetResolution),bossNumber,&window,*vectors[mapIndex]);
                            safezone.loadSafezone( sf::Vector2u(tilesetResolution, tilesetResolution),safezoneNumber,*vectors[mapIndex]);


                                    hero->setposX(vectors[mapIndex]->getTeleports()[0]->getposX()); //fixme controllare teletrasporto d'arrivo
                                    hero->setposY(vectors[mapIndex]->getTeleports()[0]->getposY());
                                    player.setPosition(hero->getposX()*tilesetResolution,hero->getposY()*tilesetResolution);
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
                    player.move(-tilesetResolution*2, 0);

                    staminaUsed=1;
                    hero->run(-1,0);
                }else {
                    player.move(-tilesetResolution, 0);

                    hero->move(-1,0);}}

            if (RightKeyDown&&isLegalMove(*hero,1,0,*maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getTeleports()) ){
                if(LShiftKeyDown&& isLegalMove(*hero,2,0,*maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getTeleports())){
                    player.move(tilesetResolution*2, 0);

                    staminaUsed=1;
                    hero->run(1,0);
                }else {
                    player.move(tilesetResolution, 0);

                    hero->move(1,0);}}

            if (UpKeyDown&&isLegalMove(*hero,0,1,*maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getTeleports()) ){
                if(LShiftKeyDown&& isLegalMove(*hero,0,2,*maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getTeleports())){
                    player.move(0, tilesetResolution*2);

                    staminaUsed=1;
                    hero->run(0,1);
                }else{
                    player.move(0, tilesetResolution);

                    hero->move(0,1);}}

            if (DownKeyDown&&isLegalMove(*hero,0,-1,*maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getTeleports()) ){
                if(LShiftKeyDown&& isLegalMove(*hero,0,-2,*maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(), &vectors[mapIndex]->getTeleports())){
                    player.move(0, -tilesetResolution*2);

                    staminaUsed=1;
                    hero->run(0,-1);
                }else {
                    player.move(0, -tilesetResolution);

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
            stamina.setSize(sf::Vector2f (hero->getStamina()/10*tilesetResolution, HudBarsHeigth));
            life.setSize(sf::Vector2f (hero->getHp()/10*tilesetResolution, HudBarsHeigth));

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






            window.draw(object);
            window.draw(life);
            window.draw(stamina);
            window.draw(Potion);
            window.draw(potionIcon);

            if(makeText) {
                window.draw(box);
                if(itemText){
                    if(tutorialItem==false){

                        objectInteraction.blackBox(box.getPosition().x,box.getPosition().y,"Per raccogliere gli oggetti premi R","Per usare le pozioni premi B",&window,false);

                    }
                }else if(safezoneText){
                    if(tutorialSafezone==false){

                        objectInteraction.blackBox(box.getPosition().x,box.getPosition().y,"Hai trovato una fonte di luce","Per usarne il potere premi T",&window,false);

                    }
                }else if(teleportText){
                    if(tutorialTeleport){

                        objectInteraction.blackBox(box.getPosition().x,box.getPosition().y,"Il teletrasporto emana un'aura misteriosa...","",&window,
                                                   false);

                    }else {
                        objectInteraction.blackBox(box.getPosition().x,box.getPosition().y,"Per usare il potere del teletrasporto premere P o O","",&window,
                                                   false);//P scorre in avanti mentre  O scorre indietro
                    }


                }



            }
            window.display();
        }
    }
    for(int i=0;i<numberMap;i++){
        delete maps[i];
        delete vectors[i];
    }
    delete hero;
    Game.stop();
    return 0;
}