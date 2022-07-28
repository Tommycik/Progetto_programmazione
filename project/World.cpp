//
// Created by tommy on 16/06/2022.
//

#include "World.h"



void World::savePlayer(int map, Mario &player,bool tutorialItem,bool tutorialSafezone,bool tutorialTeleport/*, int littleStatus*/) const{
    std::ofstream out;
    out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    // try {
    out.open("playerSave/save.txt",std::ios_base::trunc);
    out << map << std::endl;
    //out << littleStatus << std::endl;
    out << player.getHp() << std::endl;
    out <<player.getStamina()<< std::endl;
    out <<player.getPotionNum()<< std::endl;
    out <<player.getMaxHp()<< std::endl;
    out <<player.getMaxStam()<< std::endl;
    out <<player.getMovements()<< std::endl;
    out <<player.getposX()<< std::endl;
    out <<player.getposY()<< std::endl;
    out <<tutorialItem<< std::endl;
    out <<tutorialSafezone<< std::endl;
    out <<tutorialTeleport<< std::endl;
    out << player.getBossKilled() << std::endl;
    out << player.getDistanceWalked() << std::endl;
    out << player.getGameTime() << std::endl;
    out << player.getPotionTaken() << std::endl;
    out << player.getSafezoneUsed() << std::endl;
    out << player.getTeleported() << std::endl;
    out << player.getDeaths() << std::endl;
    out.close();

}


bool World::loadPlayer(int &mapIndex,Mario &player,bool &tutorialItem,bool &tutorialSafezone,bool &tutorialTeleport) {

    of.exceptions(std::ifstream::failbit);
    try {
        of.open("playerSave/save.txt");
    } catch (std::ios_base::failure& e) {

        return false;
    }
    std::string fileLine;
    std::getline(of, fileLine);
    try {

        mapIndex=(std::stoi(fileLine));
        std::getline(of, fileLine);
        player.setHp(std::stoi(fileLine));//fixme non riporta la vita corretta,la vita massima sì
        std::getline(of, fileLine);
        player.setStamina(std::stoi(fileLine));
        std::getline(of, fileLine);
        player.potionNumSave(std::stoi(fileLine));
        std::getline(of, fileLine);
        player.maxHpSave(std::stoi(fileLine));
        std::getline(of, fileLine);
        player.maxStamSave(std::stoi(fileLine));
        std::getline(of, fileLine);
        player.setMovements(std::stoi(fileLine));
        std::getline(of, fileLine);
        player.setposX(std::stoi(fileLine));
        std::getline(of, fileLine);
        player.setposY(std::stoi(fileLine));
        std::getline(of, fileLine);
        tutorialItem=(std::stoi(fileLine));
        std::getline(of, fileLine);
        tutorialSafezone=(std::stoi(fileLine));
        std::getline(of, fileLine);
        tutorialTeleport=(std::stoi(fileLine));
        std::getline(of, fileLine);
        player.setBossKilled((std::stoi(fileLine)));
        std::getline(of, fileLine);
        player.setDistanceWalked((std::stoi(fileLine)));
        std::getline(of, fileLine);
        player.setGameTime((std::stoi(fileLine)));
        std::getline(of, fileLine);
        player.setPotionTaken((std::stoi(fileLine)));
        std::getline(of, fileLine);
        player.setSafezoneUsed((std::stoi(fileLine)));
        std::getline(of, fileLine);
        player.setTeleported((std::stoi(fileLine)));
        std::getline(of, fileLine);
        player.setDeaths((std::stoi(fileLine)));

    } catch (std::out_of_range &e) {
        throw std::out_of_range("Can not set vector tile at x: ");
    }




    of.close();
    return true;


}
bool World::creation(Mario &hero,int monsterNumber,int objectNumber,int safezoneNumber,int bossNumber ,int numberMap,long oldseed,int minRoomsNumber,int &mapIndex,bool &tutorialItem,bool &tutorialSafezone,bool &tutorialTeleport,std::string *saves,std::string *names,std::string *savesVec, std::unique_ptr<Spawner> *vectors,std::unique_ptr<Dungeonarea> *maps) {
    bool playerReboot=false;
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

    if(!this->loadPlayer(mapIndex,hero,tutorialItem,tutorialSafezone,tutorialTeleport)) {

        int startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 2));
        int startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 2));
        while(!(findFreeMapTile(startX, startY, *maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getSafezones()))){
            startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 2));
            startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 2));
        }
        hero.setposX(startX);
        hero.setposY(startY);
    }
    return true;
}

int World::playerMovementUpdater(Mario &hero, Dungeonarea &maps, Spawner &vectors, sf::RectangleShape &player,
                         float tilesetResolution,bool &run,int &state) {
    float movement=1;
    float decimalMove=0.25;
    float movementRunning=2/*1.25*/;
    bool LeftKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool RightKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool UpKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool DownKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool LShiftKeyDown =sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

    int staminaUsed=0;
    state=0;
    run=false;

    if(RightKeyDown||UpKeyDown||DownKeyDown||LeftKeyDown){

        if(LShiftKeyDown){
            if(hero.getStamina()<=0)
                LShiftKeyDown = false;

            run=true;
        }
        if(LeftKeyDown){
            state=1;
        }else{
            state=2;
        }
    }

    if (LeftKeyDown &&isLegalMove(hero,-movement,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){

        if(LShiftKeyDown&& isLegalMove(hero,-movementRunning,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){
            player.move(-tilesetResolution*movementRunning, 0);

            staminaUsed=1;
            hero.run(-1,0);
        }else {
            player.move(-tilesetResolution*movement, 0);

            hero.move(-1,0);
        }
    }else if (LeftKeyDown &&isLegalMove(hero,-decimalMove,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {

        player.move(-tilesetResolution*decimalMove, 0);

        hero.move(-decimalMove,0);

    }else if (LeftKeyDown &&isLegalMove(hero,-2*decimalMove,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {

        player.move(-tilesetResolution*2*decimalMove, 0);

        hero.move(-2*decimalMove,0);

    }

        if (RightKeyDown&&isLegalMove(hero,movement,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports()) ){
        if(LShiftKeyDown&& isLegalMove(hero,movementRunning,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){
            player.move(tilesetResolution*movementRunning, 0);

            staminaUsed=1;
            hero.run(1,0);
        }else {
            player.move(tilesetResolution*movement, 0);

            hero.move(1,0);
        }
    }else if (RightKeyDown &&isLegalMove(hero,decimalMove,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {

            player.move(tilesetResolution*decimalMove, 0);

            hero.move(decimalMove,0);

        }else if (RightKeyDown &&isLegalMove(hero,2*decimalMove,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {

player.move(tilesetResolution*2*decimalMove, 0);

hero.move(2*decimalMove,0);

}

    if (UpKeyDown&&isLegalMove(hero,0,movement,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports()) ){
        if(LShiftKeyDown&& isLegalMove(hero,0,movementRunning,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){
            player.move(0, tilesetResolution*movementRunning);

            staminaUsed=1;
            hero.run(0,1);
        }else{
            player.move(0, tilesetResolution*movement);

            hero.move(0,1);
        }
    }else if (UpKeyDown &&isLegalMove(hero,0,decimalMove,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {

        player.move(0, tilesetResolution*decimalMove);

        hero.move(0,decimalMove);

    }else if (UpKeyDown &&isLegalMove(hero,0,2*decimalMove,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {

        player.move(0, tilesetResolution*2*decimalMove);

        hero.move(0,2*decimalMove);

    }

    if (DownKeyDown&&isLegalMove(hero,0,-movement,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports()) ){
        if(LShiftKeyDown&& isLegalMove(hero,0,-movementRunning,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(), &vectors.getTeleports())){
            player.move(0, -tilesetResolution*movementRunning);

            staminaUsed=1;
            hero.run(0,-1);
        }else {
            player.move(0, -tilesetResolution*movement);

            hero.move(0,-1);
        }
    }else if (DownKeyDown &&isLegalMove(hero,0,-decimalMove,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {

        player.move(0, -tilesetResolution*decimalMove);

        hero.move(0,-decimalMove);

    }else if (DownKeyDown &&isLegalMove(hero,0,-2*decimalMove,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {

        player.move(0, -tilesetResolution*2*decimalMove);

        hero.move(0,-2*decimalMove);

    }
    player.setPosition(hero.getposX()*tilesetResolution,hero.getposY()*tilesetResolution);

    return staminaUsed;
}

bool World::initialize(Mario &hero, int &mapIndex, bool &tutorialItem, bool &tutorialSafezone, bool &tutorialTeleport,int &HudBarsHeigth, int &numberMap, TileMap &map/*, TileMap &object*/, TileMap &teleport,
                       TileMap &safezone, Hud &hud, sf::View &view1, sf::RectangleShape &player,
                       sf::Texture &playerTexture, float tilesetResolution, std::unique_ptr<Dungeonarea> *maps,std::unique_ptr<Spawner> *vectors) {



    if(!playerTexture.loadFromFile("assets/mario.png")){
        return false;
    }
    playerTexture.setSmooth(false);
    player.setTexture(&playerTexture);
    //hero.setHp(50);
    player.setPosition(hero.getposX()*tilesetResolution,hero.getposY()*tilesetResolution);
    player.setOrigin(1,7);
    player.setScale(1.2,1.7);

    view1.setCenter(player.getPosition());

    if(!(hud.hudSetter(hero,tilesetResolution,HudBarsHeigth))){
        return false;
    }
    if(!teleport.loadTexture("assets/portalRings1.png")){
        return false;
    }
    if(!safezone.loadTexture("assets/pixelSet.png")){
        return false;
    }

    return true;
}
