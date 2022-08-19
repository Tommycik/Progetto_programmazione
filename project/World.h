//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_WORLD_H
#define MAIN_WORLD_H
#include "Mario.h"
#include "Littlelight.h"
#include <fstream>
#include "Spawner.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Hud.h"
#include "Loader.h"
#include "Achievements.h"
#include "Skills.h"
class World :public Subject {

public:

    void savePlayer(int map,Mario &player,bool tutorialItem,bool tutorialSafezone,bool tutorialTeleport/*,int littleStatus*/) const;
    bool loadPlayer(int &mapIndex,Mario &player,bool &tutorialItem,bool &tutorialSafezone,bool &tutorialTeleport);
    float Updater(Mario &hero,Dungeonarea &maps,Spawner &vectors,sf::RectangleShape &player,bool &run,int &state);
    bool  initialize(Mario &hero,int &mapIndex, bool &tutorialItem, bool &tutorialSafezone, bool &tutorialTeleport,int &HudBarsHeigth,int &numberMap,TileMap &map,TileMap &object,TileMap &teleport,TileMap &safezone,Hud &hud, sf::View &view1,
                     sf::RectangleShape &player, sf::Texture &playerTexture,float tilesetResolution,
                     std::unique_ptr<Dungeonarea> *maps=nullptr,std::unique_ptr<Spawner> *vectors=nullptr);

    bool creation(Mario &hero,int monsterNumber,int objectNumber,int safezoneNumber,int bossNumber ,int numberMap,long oldseed,int minRoomsNumber,int &mapIndex,bool &tutorialItem,bool &tutorialSafezone,bool &tutorialTeleport,std::string saves[],
                  std::string names[],std::string savesVec[], std::unique_ptr<Spawner> *vectors,
                  std::unique_ptr<Dungeonarea> *maps);

    std::vector<std::unique_ptr<Skills>> &getSkill() ;
    int getSkillNumber() const;
    void setSkillNumber(int skillNumber);
    bool isNewSkillCreated() const;
    void setNewSkillCreated(bool newSkillCreated);

private:

    std::ifstream of;
    std::ifstream in;
    std::vector<std::string> areaSaves;
    std::vector<std::unique_ptr<Skills>> skill;
    int skillNumber=0;
    bool newSkillCreated=false;

};

#endif //MAIN_WORLD_H
