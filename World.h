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

class World {

public:

    void savePlayer(int map,Mario &player,bool tutorialItem,bool tutorialSafezone,bool tutorialTeleport/*,int littleStatus*/) const;
    bool loadPlayer(int &mapIndex,Mario &player,bool &tutorialItem,bool &tutorialSafezone,bool &tutorialTeleport);
    bool destroyer(int numberMap,Mario &hero,Spawner **vectors=nullptr, Dungeonarea **maps=nullptr);
    bool entityUpdater();
    int playerMovementUpdater(Mario &hero,Dungeonarea &maps,Spawner &vectors,sf::RectangleShape &player,float tilesetResolution,bool &run,int &state);
    bool  initialize(Mario &hero,int &mapIndex, bool &tutorialItem, bool &tutorialSafezone, bool &tutorialTeleport,int &HudBarsHeigth,int &numberMap,TileMap &map,TileMap &object,TileMap &teleport,TileMap &safezone,Hud &hud, sf::View &view1,
                     sf::RectangleShape &player, sf::Texture &playerTexture,float tilesetResolution,
                     Dungeonarea **maps=nullptr,Spawner **vectors=nullptr);

private:

    std::ifstream of;
    std::vector<std::string> areaSaves;
};

#endif //MAIN_WORLD_H
