//
// Created by tommy on 23/07/2022.
//
#include "TestSetting.h"

void ResizeView(const sf::RenderWindow &window, sf::View &view, float viewHeigth) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(viewHeigth * aspectRatio, viewHeigth);
}

TEST_F(TheClassTest, DISABLED_Menu) {
    Menu menu(&window);
    ASSERT_EQ (menu.load(), true);
    menu.show(&window, numberMap, &saves[0], &savesVec[0]);
}

TEST_F(TheClassTest, DISABLED_WorldCreation) {
    monsterNumber = 0;
    bossNumber = 0;
    ASSERT_EQ (gameSet(), true);
    Menu menu(&window);
    ASSERT_EQ (menu.load(), true);
    menu.show(&window, numberMap, &saves[0], &savesVec[0]);
    std::unique_ptr<Dungeonarea> maps[numberMap];
    std::unique_ptr<Spawner> vectors[numberMap];
    Game.play();
    hero = std::make_unique<Mario>(100, 1, 0, 0, 40, 2, 0);

    ASSERT_EQ(game.creation(*hero, monsterNumber, objectNumber, safezoneNumber, bossNumber, numberMap, oldseed,
                            minRoomsNumber, mapIndex, tutorialItem, tutorialSafezone, tutorialTeleport,
                            &saves[0], &names[0], &savesVec[0], &vectors[0], &maps[0]), true);

    TileMap map, teleport, safezone, object;
    sf::RectangleShape player(sf::Vector2f(tilesetResolution, tilesetResolution));
    sf::View view1(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(viewHeigth, viewHeigth));
    Hud hud(1);
    Textviewer objectInteraction(128, view1.getSize().x, view1.getSize().y / 6, 128);
    ASSERT_EQ (game.initialize(*hero, mapIndex, tutorialItem, tutorialSafezone, tutorialTeleport, HudBarsHeigth, numberMap,
                            map, object, teleport, safezone, hud, view1, player, playerTexture,
                            tilesetResolution, &maps[0], &vectors[0]), true);

    Animation animationPlayer(&playerTexture, sf::Vector2u(4, 4), 0.2);

    ASSERT_EQ(map.loadMap("assets/Textures-16.png", sf::Vector2u(tilesetResolution, tilesetResolution), *maps[mapIndex],
                          maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight()), true);

    while (window.isOpen()) {

        while (window.isOpen()) {
            deltaTime = clock.restart().asSeconds();
            ResizeView(window, view1, viewHeigth);

            while (window.pollEvent(Happen)) {

                switch (Happen.type) {

                    case sf::Event::Closed:
                        cancel = true;
                        break;

                    case sf::Event::KeyPressed:
                        if (Happen.key.code == sf::Keyboard::Escape) {
                            cancel = true;
                            break;
                        }

                    default:
                        break;
                }

                if (cancel) {

                    try {
                        in.open("playerSave/save.txt");
                        in.close();
                        remove("playerSave/save.txt");
                    } catch (std::ios_base::failure &e) {}

                    game.savePlayer(mapIndex, *hero, tutorialItem, tutorialSafezone, tutorialTeleport);

                    for (int i = 0; i < numberMap; i++) {

                        try {
                            in.open(savesVec[i].c_str());
                            in.close();
                            remove(savesVec[i].c_str());
                        } catch (std::ios_base::failure &e) {}

                        vectors[i]->saveVectors(savesVec[i], names[i], bossNumber, objectNumber, monsterNumber,
                                                safezoneNumber);

                    }

                    window.close();
                    Game.stop();
                }

            }

            object.loaditem(sf::Vector2u(tilesetResolution, tilesetResolution), vectors[mapIndex]->getObjectNumber(),
                            *vectors[mapIndex]);

            teleport.loadTeleport(sf::Vector2u(tilesetResolution, tilesetResolution),
                                  vectors[mapIndex]->getBossNumber(), *vectors[mapIndex]);

            safezone.loadSafezone(sf::Vector2u(tilesetResolution, tilesetResolution),
                                  vectors[mapIndex]->getSafezoneNumber(), *vectors[mapIndex]);

            player.setPosition(hero->getposX() * tilesetResolution, hero->getposY() * tilesetResolution);
            animationPlayer.updatePlayer(deltaTime, run, state);
            player.setTextureRect(animationPlayer.getUvRect());
            window.clear();
            view1.setCenter(player.getPosition());
            window.setView(view1);
            window.draw(map);
            window.draw(teleport);
            window.draw(player);
            window.draw(safezone);
            window.draw(object);
            hud.hudSow(*hero, &window, tilesetResolution, HudBarsHeigth, view1);

            if (!makeText) {
                hero->notify();
            }

            objectInteraction.show(window, view1, makeText, itemText, tutorialItem, safezoneText, tutorialSafezone,
                                   teleportText, tutorialTeleport);

            window.display();
            sf::sleep((sf::milliseconds(120)));
        }

    }

    Game.stop();
}

TEST_F(TheClassTest, mapExploration) {
    monsterNumber = 0;
    bossNumber = 1;
    ASSERT_EQ (gameSet(), true);
    Menu menu(&window);
    ASSERT_EQ (menu.load(), true);
    menu.show(&window, numberMap, &saves[0], &savesVec[0]);
    std::unique_ptr<Dungeonarea> maps[numberMap];
    std::unique_ptr<Spawner> vectors[numberMap];
    Game.play();
    hero = std::make_unique<Mario>(100, 1, 0, 0, 40, 2, 0);

    ASSERT_EQ(game.creation(*hero, monsterNumber, objectNumber, safezoneNumber, bossNumber, numberMap, oldseed,
                            minRoomsNumber, mapIndex, tutorialItem, tutorialSafezone, tutorialTeleport,
                            &saves[0], &names[0], &savesVec[0], &vectors[0], &maps[0]), true);

    TileMap map, teleport, safezone, object;
    sf::RectangleShape player(sf::Vector2f(tilesetResolution, tilesetResolution));
    sf::View view1(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(viewHeigth, viewHeigth));
    Hud hud(1);
    Achievements achievements(*hero, window, view1);
    ASSERT_EQ (achievements.load(), true);
    Textviewer objectInteraction(128, view1.getSize().x, view1.getSize().y / 6, 128);
    ASSERT_EQ (game.initialize(*hero, mapIndex, tutorialItem, tutorialSafezone, tutorialTeleport, HudBarsHeigth, numberMap,
                            map, object, teleport, safezone, hud, view1, player, playerTexture,
                            tilesetResolution, &maps[0], &vectors[0]), true);

    Animation animationPlayer(&playerTexture, sf::Vector2u(4, 4), 0.2);

    ASSERT_EQ (map.loadMap("assets/Textures-16.png", sf::Vector2u(tilesetResolution, tilesetResolution), *maps[mapIndex],
                        maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight()), true);

    bool change = false;

    while (window.isOpen()) {

        while (window.isOpen()) {
            change = false;
            staminaUsed = 0;
            teleportText = false;
            itemText = false;

            makeText = objectInteraction.checker(*vectors[mapIndex], *hero, itemText, safezoneText, teleportText,
                                                 tutorialSafezone, tutorialItem);

            deltaTime = clock.restart().asSeconds();
            hero->setGameTime(hero->getGameTime() + 0.001);
            ResizeView(window, view1, viewHeigth);

            eventControl = events.event(&window, &names[0], &savesVec[0], *hero, tutorialItem, tutorialSafezone,
                                        tutorialTeleport, mapIndex, numberMap, game, Game, map, object, teleport,
                                        safezone, &vectors[0]);

            int count = 0;
            bool found = false;

            switch (eventControl) {

                case 1:
                    window.close();
                    break;

                case 2:

                    ASSERT_EQ(map.loadMap("assets/Textures-16.png", sf::Vector2u(tilesetResolution, tilesetResolution),
                                          *maps[mapIndex], maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight()), true);

                    for (auto &gc: vectors[mapIndex]->getTeleports()) {

                        if (gc->isActivated()) {
                            found = true;
                            break;
                        }

                        count++;
                    }

                    if (found) {
                        hero->setposX(vectors[mapIndex]->getTeleports()[count]->getposX());
                        hero->setposY(vectors[mapIndex]->getTeleports()[count]->getposY());
                    } else {
                        float startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 2));
                        float startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 2));

                        while (!(findFreeMapTile(startX, startY, *maps[mapIndex], &vectors[mapIndex]->getBosses(),
                                                 &vectors[mapIndex]->getItems(), &vectors[mapIndex]->getEnemies(),
                                                 &vectors[mapIndex]->getSafezones()))) {

                            startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 2));
                            startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 2));
                        }

                        hero->setposX(startX);
                        hero->setposY(startY);
                    }

                    tutorialTeleport = true;
                    change = true;
                    break;

                default:
                    break;
            }

            staminaUsed += game.Updater(*hero, *maps[mapIndex], *vectors[mapIndex], player, view1, window, run, state);

            object.loaditem(sf::Vector2u(tilesetResolution, tilesetResolution), vectors[mapIndex]->getObjectNumber(),
                            *vectors[mapIndex]);

            teleport.loadTeleport(sf::Vector2u(tilesetResolution, tilesetResolution),
                                  vectors[mapIndex]->getBossNumber(), *vectors[mapIndex]);

            safezone.loadSafezone(sf::Vector2u(tilesetResolution, tilesetResolution),
                                  vectors[mapIndex]->getSafezoneNumber(), *vectors[mapIndex]);

            hero->stamUse(staminaUsed);
            hero->recoverStam();
            player.setPosition(hero->getposX() * tilesetResolution, hero->getposY() * tilesetResolution);
            animationPlayer.updatePlayer(deltaTime, run, state);
            player.setTextureRect(animationPlayer.getUvRect());
            window.clear();
            view1.setCenter(player.getPosition());
            window.setView(view1);
            window.draw(map);
            window.draw(teleport);
            window.draw(player);
            window.draw(safezone);
            window.draw(object);
            hud.hudSow(*hero, &window, tilesetResolution, HudBarsHeigth, view1);

            if (!makeText) {
                hero->notify();
            }

            objectInteraction.show(window, view1, makeText, itemText, tutorialItem, safezoneText, tutorialSafezone,
                                   teleportText, tutorialTeleport);

            window.display();
            sf::sleep((sf::milliseconds(120)));
        }

    }

    Game.stop();
}

TEST_F(TheClassTest, TestGame) {
    ASSERT_EQ (gameSet(), true);
    Menu menu(&window);
    ASSERT_EQ (menu.load(), true);
    menu.show(&window, numberMap, &saves[0], &savesVec[0]);
    std::unique_ptr<Dungeonarea> maps[numberMap];
    std::unique_ptr<Spawner> vectors[numberMap];
    Game.play();
    hero = std::make_unique<Mario>(100, 1, 0, 0, 40, 2, 0);

    ASSERT_EQ(game.creation(*hero, monsterNumber, objectNumber, safezoneNumber, bossNumber, numberMap, oldseed,
                            minRoomsNumber, mapIndex, tutorialItem, tutorialSafezone, tutorialTeleport,
                            &saves[0], &names[0], &savesVec[0], &vectors[0], &maps[0]), true);

    TileMap map, teleport, safezone, obstacles, skill, object, boss;
    sf::RectangleShape player(sf::Vector2f(tilesetResolution, tilesetResolution));
    sf::View view1(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(viewHeigth, viewHeigth));
    Hud hud(1);
    Achievements achievements(*hero, window, view1);
    SkillManager skillManager(game, skill);
    ASSERT_EQ (achievements.load(), true);
    Textviewer objectInteraction(128, view1.getSize().x, view1.getSize().y / 6, 128);

    ASSERT_EQ (game.initialize(*hero, mapIndex, tutorialItem, tutorialSafezone, tutorialTeleport, HudBarsHeigth, numberMap,
                            map, object, teleport, safezone, hud, view1, player,
                            playerTexture, tilesetResolution, &maps[0], &vectors[0]), true);

    Animation animationPlayer(&playerTexture, sf::Vector2u(4, 4), 0.2);

    ASSERT_EQ (map.loadMap("assets/Textures-16.png", sf::Vector2u(tilesetResolution, tilesetResolution), *maps[mapIndex],
                        maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight()), true);

    bool change = false;

    while (window.isOpen()) {

        while (window.isOpen()) {
            change = false;
            staminaUsed = 0;
            teleportText = false;
            itemText = false;

            makeText = objectInteraction.checker(*vectors[mapIndex], *hero, itemText, safezoneText, teleportText,
                                                 tutorialSafezone, tutorialItem);

            deltaTime = clock.restart().asSeconds();
            hero->setGameTime(hero->getGameTime() + 0.001);
            ResizeView(window, view1, viewHeigth);

            eventControl = events.event(&window, &names[0], &savesVec[0], *hero, tutorialItem, tutorialSafezone,
                                        tutorialTeleport, mapIndex, numberMap, game, Game, map, object, teleport,
                                        safezone, &vectors[0]);

            int count = 0;
            bool found = false;

            switch (eventControl) {

                case 1:
                    window.close();
                    break;

                case 2:

                    ASSERT_EQ(map.loadMap("assets/Textures-16.png", sf::Vector2u(tilesetResolution, tilesetResolution),
                                          *maps[mapIndex], maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight()), true);

                    for (auto &gc: vectors[mapIndex]->getTeleports()) {

                        if (gc->isActivated()) {
                            found = true;
                            break;
                        }

                        count++;
                    }

                    if (found) {
                        hero->setposX(vectors[mapIndex]->getTeleports()[count]->getposX());
                        hero->setposY(vectors[mapIndex]->getTeleports()[count]->getposY());
                    } else {
                        float startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 2));
                        float startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 2));

                        while (!(findFreeMapTile(startX, startY, *maps[mapIndex], &vectors[mapIndex]->getBosses(),
                                                 &vectors[mapIndex]->getItems(), &vectors[mapIndex]->getEnemies(),
                                                 &vectors[mapIndex]->getSafezones()))) {

                            startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 2));
                            startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 2));
                        }

                        hero->setposX(startX);
                        hero->setposY(startY);
                    }

                    tutorialTeleport = true;
                    change = true;
                    break;

                default:
                    break;
            }

            staminaUsed += game.Updater(*hero, *maps[mapIndex], *vectors[mapIndex], player, view1, window, run, state);

            obstacles.loadEnemy(sf::Vector2u(tilesetResolution, tilesetResolution),
                                vectors[mapIndex]->getMonsterNumber(), *vectors[mapIndex], change);

            object.loaditem(sf::Vector2u(tilesetResolution, tilesetResolution), vectors[mapIndex]->getObjectNumber(),
                            *vectors[mapIndex]);

            teleport.loadTeleport(sf::Vector2u(tilesetResolution, tilesetResolution),
                                  vectors[mapIndex]->getBossNumber(), *vectors[mapIndex]);

            safezone.loadSafezone(sf::Vector2u(tilesetResolution, tilesetResolution),
                                  vectors[mapIndex]->getSafezoneNumber(), *vectors[mapIndex]);

            boss.loadBoss(sf::Vector2u(tilesetResolution, tilesetResolution), vectors[mapIndex]->getBossNumber(),
                          *vectors[mapIndex], change);

            hero->stamUse(staminaUsed);
            hero->recoverStam();
            player.setPosition(hero->getposX() * tilesetResolution, hero->getposY() * tilesetResolution);
            animationPlayer.updatePlayer(deltaTime, run, state);
            player.setTextureRect(animationPlayer.getUvRect());

            ASSERT_EQ (draw(*hero, view1, player, hud, objectInteraction, map, object, teleport, safezone, obstacles,
                            skill, boss), true);

            sf::sleep((sf::milliseconds(120)));
        }

    }

    Game.stop();
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
