//
// Created by tommy on 24/07/2022.
//

#include "TestSetting.h"

TheClassTest::~TheClassTest() {}

TheClassTest::TheClassTest() {
    window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height),"try");
    window.setFramerateLimit(60);
}

bool TheClassTest::gameSet() {
    if (!Game.openFromFile("assets/gioco.wav"))
        return false;

    Game.setVolume(50.f);
    Game.setLoop(true);
    minRoomsNumber = (bossNumber + monsterNumber + objectNumber + safezoneNumber) / 2 + bossNumber;

    if ((bossNumber + monsterNumber + objectNumber + safezoneNumber) % 2 != 0)
        minRoomsNumber += (bossNumber + monsterNumber + objectNumber + safezoneNumber) % 2;

    minRoomsNumber++;

    if (minRoomsNumber < 10)
        minRoomsNumber += 10;

    return true;
}

bool TheClassTest::draw(Mario &hero, sf::View &view1, sf::RectangleShape &player, Hud &hud, Textviewer &objectInteraction,
                   TileMap &map, TileMap &object, TileMap &teleport, TileMap &safezone, TileMap &obstacles,
                   TileMap &skill, TileMap &boss) {

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
    window.draw(boss);
    hud.hudSow(hero, &window, tilesetResolution, HudBarsHeigth, view1);
    previousHp = hero.getHp();

    if (!makeText) {
        hero.notify();
    }

    if (previousHp != hero.getHp()) {
        goto respawn;
    }

    objectInteraction.show(window, view1, makeText, itemText, tutorialItem, safezoneText, tutorialSafezone,
                           teleportText, tutorialTeleport);

    window.display();
    return true;
}

