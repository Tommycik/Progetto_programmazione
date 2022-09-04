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
        player.setHp(std::stod(fileLine));
        std::getline(of, fileLine);
        player.setStamina(std::stod(fileLine));
        std::getline(of, fileLine);
        player.potionNumSave(std::stoi(fileLine));
        std::getline(of, fileLine);
        player.maxHpSave(std::stod(fileLine));
        std::getline(of, fileLine);
        player.maxStamSave(std::stod(fileLine));
        std::getline(of, fileLine);
        player.setMovements(std::stod(fileLine));
        std::getline(of, fileLine);
        player.setposX(std::stod(fileLine));
        std::getline(of, fileLine);
        player.setposY(std::stod(fileLine));
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
        player.setGameTime((std::stod(fileLine)));
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
    const int maxRoomX=30;
    const int maxRoomY=30;
    const int minRoomX=20;
    const int minRoomY=20;
    try {
        for(int i=0;i<numberMap;i++){

            maps[i] =std::make_unique<Dungeonarea>(oldseed, minRoomsNumber*(maxRoomX/2)+1, minRoomsNumber*(maxRoomY/2)+1, minRoomX, minRoomY,maxRoomX,maxRoomY, i, minRoomsNumber*100, minRoomsNumber*(minRoomX/2), minRoomsNumber*(minRoomY/2), names[i], saves[i],minRoomsNumber);
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

        float startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 2));
        float startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 2));
        while(!(findFreeMapTile(startX, startY, *maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getSafezones()))){
            startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 2));
            startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 2));
        }
        hero.setposX(startX);
        hero.setposY(startY);
    }
    return true;
}

float World::Updater(Mario &hero, Dungeonarea &maps, Spawner &vectors, sf::RectangleShape &player,bool &run,int &state) {

    float decimalMove=0.25;
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

    if (LeftKeyDown &&isLegalMove(hero,-hero.getMovements(),0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){

        if(LShiftKeyDown&& isLegalMove(hero,-hero.getRunningMovement(),0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){
            staminaUsed=1;
            hero.run(-hero.getRunningMovement(),0);
        }else {
            hero.move(-hero.getMovements(),0);
        }

    }else if (LeftKeyDown &&isLegalMove(hero,-2*decimalMove,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {
        hero.move(-2*decimalMove,0);
    }else if (LeftKeyDown &&isLegalMove(hero,-2*decimalMove,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {
        hero.move(-2*decimalMove,0);
    }

    if (RightKeyDown&&isLegalMove(hero,hero.getMovements(),0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports()) ){

        if(LShiftKeyDown&& isLegalMove(hero,hero.getRunningMovement(),0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){
            staminaUsed=1;
            hero.run(hero.getRunningMovement(),0);
        }else {
            hero.move(hero.getMovements(),0);
        }

    }else if (RightKeyDown &&isLegalMove(hero,2*decimalMove,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {
        hero.move(2*decimalMove,0);
    }else if (RightKeyDown &&isLegalMove(hero,2*decimalMove,0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {
        hero.move(2*decimalMove,0);
    }

    if (UpKeyDown&&isLegalMove(hero,0,hero.getMovements(),maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports()) ){

        if(LShiftKeyDown&& isLegalMove(hero,0,hero.getRunningMovement(),maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){
            staminaUsed=1;
            hero.run(0,hero.getRunningMovement());
        }else{
            hero.move(0,hero.getMovements());
        }

    }else if (UpKeyDown &&isLegalMove(hero,0,2*decimalMove,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {
        hero.move(0,2*decimalMove);
    }else if (UpKeyDown &&isLegalMove(hero,0,2*decimalMove,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {
        hero.move(0,2*decimalMove);
    }

    if (DownKeyDown&&isLegalMove(hero,0,-hero.getMovements(),maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports()) ){

        if(LShiftKeyDown&& isLegalMove(hero,0,-hero.getRunningMovement(),maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(), &vectors.getTeleports())){
            staminaUsed=1;
            hero.run(0,-hero.getRunningMovement());
        }else {
            hero.move(0,-hero.getMovements());
        }

    }else if (DownKeyDown &&isLegalMove(hero,0,-2*decimalMove,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {
        hero.move(0,-2*decimalMove);
    }else if (DownKeyDown &&isLegalMove(hero,0,-2*decimalMove,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())) {
        hero.move(0,-2*decimalMove);
    }
    legalDamage(&hero,&vectors.getEnemies(),&vectors.getBosses(),&skill);

    int count=0;
    bool found=false;
    if(hero.getHp()<=0){
        for(auto &gc:vectors.getSafezones()){
            if(gc->isUsed()){
                found=true;
                break;
            }
            count++;
        }
        if(found){
            hero.setposX(vectors.getSafezones()[count]->getposX());
            hero.setposY(vectors.getSafezones()[count]->getposY());
        }else{

            float startX = maps.getRand(0, (maps.getWidth() - 2));
            float startY = maps.getRand(0, (maps.getHeight() - 2));
            while(!(findFreeMapTile(startX, startY, maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getSafezones()))){
                startX = maps.getRand(0, (maps.getWidth() - 2));
                startY = maps.getRand(0, (maps.getHeight() - 2));
            }
            hero.setposX(startX);
            hero.setposY(startY);
        }
    }else{
        if(hero.getTimeSinceDamage()!=0.00){
            hero.setTimeSinceDamage(-1);
        }
    }
    count=0;
    int skillToErase[skillNumber];
    for(auto &gl:skill){
        skillToErase[count]=0;
        gl->setChecked(true);
        gl->targetSearch(vectors.getBosses(),vectors.getEnemies(),hero);
        if(gl->isTargetLost()==false||gl->getHp()<=0){
            gl->behaviour(*gl->getTarget());
            for(auto &gn:skill){
                if(!gn->isChecked()&& l2Distance(*gn,gl->getposX()+gl->getDirectX(),gl->getposY()+gl->getDirectY())<=1){
                    gn->receiveDamage(gl->getDamage());
                    gl->receiveDamage(gn->getDamage());
                }
            }
            if(gl->getHp()>0&&(l2Distance(*gl->getTarget(),gl->getposX()+gl->getDirectX(),gl->getposY()+gl->getDirectY())!=0)&&isLegalMove(*gl,gl->getDirectX(),gl->getDirectY(),maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){
                gl->move((gl->getDirectX()),gl->getDirectY());
            }else{
                if(l2Distance(*gl->getTarget(),gl->getposX()+gl->getDirectX(),gl->getposY()+gl->getDirectY())<=gl->getRadius()){
                    gl->getTarget()->receiveDamage(gl->getDamage());
                }
                for(auto &gb:vectors.getEnemies()){
                    if(gb->isTarget()==false&&l2Distance(*gb,gl->getposX()+gl->getDirectX(),gl->getposY()+gl->getDirectY())<=gl->getRadius()){
                        gb->receiveDamage(gl->getDamage());
                    }
                }
                for(auto &gb:vectors.getBosses()){
                    if(gb->isTarget()==false&&l2Distance(*gb,gl->getposX()+gl->getDirectX(),gl->getposY()+gl->getDirectY())<=gl->getRadius()){
                        gb->receiveDamage(gl->getDamage());
                    }
                }
                gl->getTarget()->setTarget(false);
                skillToErase[count]=1;
                skillNumber--;
            }
        }else{
            skillToErase[count]=1;
            skillNumber--;
        }
        gl->setChecked(false);
        count++;
    }
    found=false;
    count=0;
    int erased=0;
    for(auto gd:skillToErase){
        if(gd==1){
            skill.erase(skill.begin()+count-erased);
            erased++;
            newSkillCreated=true;
        }
        count++;
    }

    int enemyToErase[vectors.getMonsterNumber()];
    count=0;
    for(auto &gp:vectors.getEnemies()){

        enemyToErase[count]=0;
        if(gp->getHp()!=0){
            gp->behaviour(hero);
            if(gp->isActivated()==true){
                gp->setChecked(true);
                if((l2Distance(hero,gp->getposX()+gp->getDirectX(),gp->getposY()+gp->getDirectY())>=1)&&isLegalMove(*gp,gp->getDirectX(),gp->getDirectY(),maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){
                    gp->move((gp->getDirectX()),gp->getDirectY());
                }else  if((l2Distance(hero,gp->getposX()+gp->getDirectX(),gp->getposY())>=1)&&isLegalMove(*gp,gp->getDirectX(),0,maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){
                    gp->move((gp->getDirectX()),0);
                }else  if((l2Distance(hero,gp->getposX(),gp->getposY()+gp->getDirectY())>=1)&&isLegalMove(*gp,0,gp->getDirectY(),maps,&vectors.getBosses(),&vectors.getItems(),&vectors.getEnemies(),&vectors.getTeleports())){
                    gp->move(0,gp->getDirectY());
                }
                gp->setChecked(false);
            }
        }else{
            enemyToErase[count]=1;
        }
        count++;
    }
    count=0;
    erased=0;
    for(auto gd:enemyToErase){
        if(gd==1){
            vectors.getEnemies().erase(vectors.getEnemies().begin()+count-erased);
            erased++;
            vectors.setMonsterNumber(-1);
        }
        count++;
    }

    //todo aggiungere boss(controlare anche su spawner) controllo con skillused di entity se qualcuno usa un abilità newSkillCreated==true

    return staminaUsed;
}

bool World::initialize(Mario &hero, int &mapIndex, bool &tutorialItem, bool &tutorialSafezone, bool &tutorialTeleport,int &HudBarsHeigth, int &numberMap, TileMap &map, TileMap &object, TileMap &teleport,
                       TileMap &safezone, Hud &hud, sf::View &view1, sf::RectangleShape &player,
                       sf::Texture &playerTexture, float tilesetResolution, std::unique_ptr<Dungeonarea> *maps,std::unique_ptr<Spawner> *vectors) {



    if(!playerTexture.loadFromFile("assets/mario.png")){
        return false;
    }
    playerTexture.setSmooth(false);
    player.setTexture(&playerTexture);
    //hero.setHp(50); //per testare cure
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
    if(!object.loadTexture("assets/potions.png")){
        return false;
    }


    return true;
}

 std::vector<std::unique_ptr<Skills>> &World::getSkill()  {
    return skill;
}

int World::getSkillNumber() const {
    return skillNumber;
}

void World::setSkillNumber(int skillNumber) {
    World::skillNumber += skillNumber;
}

bool World::isNewSkillCreated() const {
    return newSkillCreated;
}

void World::setNewSkillCreated(bool newSkillCreated) {
    World::newSkillCreated = newSkillCreated;
}
