//
// Created by tommy on 24/07/2022.
//

#include "TestSetting.h"

TheClassTest::~TheClassTest() {
}

TheClassTest::TheClassTest() {
    window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "try"/*,sf::Style::Fullscreen*/);
    window.setFramerateLimit(60);
}

bool TheClassTest::gameSet() {
    if (!Game.openFromFile("assets/gioco.wav"))
        return false; // error

    Game.setVolume(50.f);
    Game.setLoop(true);
    if((bossNumber+monsterNumber+objectNumber+safezoneNumber)%3!=0)
        minRoomsNumber++;

    minRoomsNumber++;
    return true;
}

bool TheClassTest::draw(Mario &hero, sf::View &view1,sf::RectangleShape &player,Hud &hud, Textviewer &objectInteraction,TileMap &map,TileMap &object,TileMap &teleport,TileMap &safezone,TileMap &obstacles,TileMap &skill) {
respawn:
    game.notify();
    window.clear();
    view1.setCenter(player.getPosition());
    window.setView(view1);
    window.draw(map);
    window.draw(skill);
    window.draw(teleport);
    window.draw(obstacles);
    window.draw(player);
    window.draw(safezone);
    window.draw(object);
    hud.hudSow(hero,&window,tilesetResolution,HudBarsHeigth,view1);
    float previousHp=hero.getHp();
    if(!makeText){
        hero.notify();
    }
    if(previousHp!=hero.getHp()){
        goto respawn;
    }

    objectInteraction.show(window,view1,makeText,itemText,tutorialItem,safezoneText,tutorialSafezone,teleportText,tutorialTeleport);
    window.display();
    return true;
}

bool TheClassTest::creation(std::unique_ptr<Spawner> *vectors,std::unique_ptr<Dungeonarea> *maps) {
    Game.play();
    try {
        for(int i=0;i<numberMap;i++){

            maps[i] =std::make_unique<Dungeonarea>(oldseed, minRoomsNumber*20+1, minRoomsNumber*20+1, 15, 15,30,30, i, 70, minRoomsNumber*10, minRoomsNumber*15, minRoomsNumber*15, names[i], saves[i],minRoomsNumber);
            if(!maps[i]->loadMap(saves[i],names[i])){
                try {
                    in.open(savesVec[i].c_str());
                    in.close();
                    remove(savesVec[i].c_str());
                } catch (std::ios_base::failure& e) {}

                maps[i]->createDungeon();
                playerReboot=true;
                oldseed=maps[i]->getOldseed()+maps[i]->getRand(0,1000);
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
    for(int i=0;i<numberMap;i++) {
        vectors[i]=std::make_unique<Spawner>(false,*maps[i],monsterNumber,objectNumber,safezoneNumber,bossNumber);
        if ((!vectors[i]->loadVectors(savesVec[i],names[i],*maps[i]))) {

            playerReboot=true;
            vectors[i]->saveVectors(savesVec[i],names[i],bossNumber, objectNumber, monsterNumber, safezoneNumber);
        }
    }
    if(playerReboot){
        try {
            in.open("playerSave/save.txt");
            in.close();
            remove("playerSave/save.txt");
        } catch (std::ios_base::failure& e) {}
    }
    hero=std::make_unique<Mario>(100, 1, 0, 0,40,2,0);
    if(!game.loadPlayer(mapIndex,*hero,tutorialItem,tutorialSafezone,tutorialTeleport)) {

        float startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 2));
        float startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 2));
        while(!(findFreeMapTile(startX, startY, *maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getSafezones()))){
            startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 2));
            startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 2));
        }
        hero->setposX(startX);
        hero->setposY(startY);
    }
    return true;
}
