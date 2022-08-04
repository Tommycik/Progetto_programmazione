//
// Created by tommy on 24/07/2022.
//

#ifndef MAIN_TESTSETTING_H
#define MAIN_TESTSETTING_H

#include "gtest/gtest.h"
#include "../Animation.h"
#include "../Menu.h"
#include "../Events.h"
#include "../Achievements.h"

class TheClassTest : public ::testing::Test {
protected:

    TheClassTest();
    virtual ~TheClassTest();
    bool gameSet();
    bool draw(Mario &hero, sf::View &view1,sf::RectangleShape &player,Hud &hud, Textviewer &objectInteraction,TileMap &map,TileMap &object,TileMap &teleport,TileMap &safezone,TileMap &obstacles);
    bool creation(std::unique_ptr<Spawner> *vectors=nullptr,std::unique_ptr<Dungeonarea> *maps=nullptr);

    int monsterNumber=15;
    int objectNumber=5;
    int safezoneNumber=2;
    int bossNumber=5;
    int numberMap=2;
    int mapIndex=0;
    int minRoomsNumber=(bossNumber+monsterNumber+objectNumber+safezoneNumber)/3+bossNumber;
    bool playerReboot=false;
    long oldseed=0;
    const float tilesetResolution=16;
    const int viewHeigth = 300;
    std::ifstream in;
    sf::RenderWindow window;
    sf::Music Game;
    World game;
    bool tutorialItem=false,tutorialSafezone=false,tutorialTeleport=false;
    std::unique_ptr<Mario> hero;
    sf::Texture playerTexture;
    int HudBarsHeigth=14;
    int state=0;
    bool run=false;
    float staminaUsed=0;
    bool makeText=false,teleportText=false,itemText=false,safezoneText=false;
    sf::Clock clock;
    float deltaTime=0.0f;
    int eventControl=0;
    sf::Event Happen;
    bool cancel=false;
    Events events;

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
};
#endif //MAIN_TESTSETTING_H
