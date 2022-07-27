//
// Created by tommy on 10/07/2022.
//

#ifndef MAIN_EVENTS_H
#define MAIN_EVENTS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Dungeonarea.h"
#include "World.h"

class Events {

public:

    int event(sf::RenderWindow *window,std::string *saves,std::string *names,std::string *savesVec,Mario &hero,bool &tutorialItem,
              bool &tutorialSafezone,bool &tutorialTeleport,int &mapIndex,int numberMap,World &game,
              int bossNumber,int monsterNumber,int objectNumber,int safezoneNumber,sf::Music &Game,TileMap &map,TileMap &object,TileMap &teleport,TileMap &safezone,
              std::unique_ptr<Spawner> *vectors=nullptr,std::unique_ptr<Dungeonarea> *maps=nullptr);

private:

    sf::Event Happen;
    std::ifstream is;
    bool cancel=false;
};


#endif //MAIN_EVENTS_H
