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
    } catch (std::out_of_range &e) {
        throw std::out_of_range("Can not set vector tile at x: ");
    }




    of.close();
    return true;


}

bool World::destroyer(int numberMap,Mario &hero,Spawner **vectors, Dungeonarea **maps) {
    for(int i=0;i<numberMap;i++){
        maps[i]->~Dungeonarea();
        vectors[i]->~Spawner();
    }
    delete &hero;


    return true;
}

int World::playerMovementUpdater(Mario &hero, Dungeonarea &maps, Spawner &vectors, sf::RectangleShape &player,
                         float tilesetResolution,bool &run,int &state) {
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

            run=true;}

        if(LeftKeyDown){
            state=1;
        }else{
            state=2;}
    }


    if (LeftKeyDown &&isLegalMove(hero,-1,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){

        if(LShiftKeyDown&& isLegalMove(hero,-2,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){
            player.move(-tilesetResolution*2, 0);

            staminaUsed=1;
            hero.run(-1,0);
        }else {
            player.move(-tilesetResolution, 0);

            hero.move(-1,0);}}

    if (RightKeyDown&&isLegalMove(hero,1,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports()) ){
        if(LShiftKeyDown&& isLegalMove(hero,2,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){
            player.move(tilesetResolution*2, 0);

            staminaUsed=1;
            hero.run(1,0);
        }else {
            player.move(tilesetResolution, 0);

            hero.move(1,0);}}

    if (UpKeyDown&&isLegalMove(hero,0,1,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports()) ){
        if(LShiftKeyDown&& isLegalMove(hero,0,2,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){
            player.move(0, tilesetResolution*2);

            staminaUsed=1;
            hero.run(0,1);
        }else{
            player.move(0, tilesetResolution);

            hero.move(0,1);}}

    if (DownKeyDown&&isLegalMove(hero,0,-1,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports()) ){
        if(LShiftKeyDown&& isLegalMove(hero,0,-2,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(), &vectors.getTeleports())){
            player.move(0, -tilesetResolution*2);

            staminaUsed=1;
            hero.run(0,-1);
        }else {
            player.move(0, -tilesetResolution);

            hero.move(0,-1);}}

    return staminaUsed;
}

bool World::initialize(Mario &hero, int &mapIndex, bool &tutorialItem, bool &tutorialSafezone, bool &tutorialTeleport,int &HudBarsHeigth, int &numberMap, TileMap &map, TileMap &object, TileMap &teleport,
                       TileMap &safezone, Hud &hud, sf::View &view1, sf::RectangleShape &player,
                       sf::Texture &playerTexture, float &tilesetResolution, Dungeonarea **maps, Spawner **vectors) {

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

    if(!playerTexture.loadFromFile("assets/mario.png")){

        this->destroyer(numberMap,hero,&vectors[0],&maps[0]);
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
        this->destroyer(numberMap,hero,&vectors[0],&maps[0]);
        return false;
    }
    if (!map.loadMap("assets/Textures-16.png", sf::Vector2u(tilesetResolution, tilesetResolution), *maps[mapIndex], maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight())){

        this->destroyer(numberMap,hero,&vectors[0],&maps[0]);
        return false;
    }
    if(!object.loadTexture("assets/potions.png")){

        this->destroyer(numberMap,hero,&vectors[0],&maps[0]);
        return false;
    }
    if(!teleport.loadTexture("assets/portalRings1.png")){

        this->destroyer(numberMap,hero,&vectors[0],&maps[0]);
        return false;
    }
    if(!safezone.loadTexture("assets/pixelSet.png")){

        this->destroyer(numberMap,hero,&vectors[0],&maps[0]);
        return false;
    }
    object.loaditem( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getObjectNumber(),*vectors[mapIndex]);
    teleport.loadTeleport( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getBossNumber(),*vectors[mapIndex]);
    safezone.loadSafezone( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getSafezoneNumber(),*vectors[mapIndex]);
return true;
}
