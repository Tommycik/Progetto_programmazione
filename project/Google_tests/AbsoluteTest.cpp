//
// Created by tommy on 23/07/2022.
//
#include "TestSetting.h"

void ResizeView(const sf::RenderWindow &window, sf::View &view,int viewHeigth) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(viewHeigth * aspectRatio, viewHeigth);
}

int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(TheClassTest,DISABLED_Menu){
    Menu menu(&window);
    ASSERT_EQ (menu.load(), true);
    menu.show(&window,numberMap,&saves[0],&savesVec[0]);

}

TEST_F(TheClassTest,WorldCreation){

    ASSERT_EQ (gameSet(), true);
    Menu menu(&window);
    ASSERT_EQ (menu.load(), true);

    menu.show(&window,numberMap,&saves[0],&savesVec[0]);
    std::unique_ptr<Dungeonarea> maps[numberMap];
    std::unique_ptr<Spawner> vectors[numberMap];
    ASSERT_EQ(creation(&vectors[0],&maps[0]),true);

    TileMap map,teleport,safezone;
    sf::RectangleShape player(sf::Vector2f(tilesetResolution, tilesetResolution));
    sf::View view1(sf::Vector2f (0.0f,0.0f),sf::Vector2f (viewHeigth,viewHeigth));
    Hud hud(1);
    Textviewer objectInteraction(window.getSize().y/5,window.getSize().x,128,viewHeigth);
    ASSERT_EQ (game.initialize(*hero,mapIndex,tutorialItem,tutorialSafezone,tutorialTeleport,HudBarsHeigth,numberMap,map/*,object*/,teleport,safezone,hud,view1,player,
                               playerTexture,tilesetResolution,&maps[0],&vectors[0]), true);

    Animation animationPlayer(&playerTexture,sf::Vector2u (4,4),0.2);

    ASSERT_EQ(map.loadMap("assets/Textures-16.png", sf::Vector2u(tilesetResolution, tilesetResolution), *maps[mapIndex], maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight()),true);


    while (window.isOpen()) {

        while (window.isOpen()) {

            TileMap object;
            ASSERT_EQ (object.loadTexture("assets/potions.png"), true);
            deltaTime=clock.restart().asSeconds();
            ResizeView(window,view1,viewHeigth);
            while (window.pollEvent(Happen)){

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
                if (cancel){
                    try {
                        in.open("playerSave/save.txt");
                        in.close();
                        remove("playerSave/save.txt");
                    } catch (std::ios_base::failure& e) {}

                    game.savePlayer(mapIndex,*hero,tutorialItem,tutorialSafezone,tutorialTeleport);
                    for(int i=0;i<numberMap;i++) {
                        try {
                            in.open(savesVec[i].c_str());
                            in.close();
                            remove(savesVec[i].c_str());
                        } catch (std::ios_base::failure& e) {}

                        vectors[i]->saveVectors(savesVec[i],names[i],bossNumber, objectNumber, monsterNumber, safezoneNumber);
                    }
                    window.close();
                    Game.stop();
                }
            }

            object.loaditem( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getObjectNumber(),*vectors[mapIndex]);
            teleport.loadTeleport( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getBossNumber(),*vectors[mapIndex]);
            safezone.loadSafezone( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getSafezoneNumber(),*vectors[mapIndex]);

            player.setPosition(hero->getposX()*tilesetResolution,hero->getposY()*tilesetResolution);
            animationPlayer.updatePlayer(deltaTime,run,state);
            player.setTextureRect(animationPlayer.getUvRect());
            ASSERT_EQ (draw(*hero,view1,player,hud,objectInteraction,map,object,teleport,safezone), true);
            sf::sleep((sf::milliseconds(120)));
        }
}

Game.stop();
}




TEST_F(TheClassTest,TestMap){

    ASSERT_EQ (gameSet(), true);
    Menu menu(&window);
    ASSERT_EQ (menu.load(), true);

    menu.show(&window,numberMap,&saves[0],&savesVec[0]);
    std::unique_ptr<Dungeonarea> maps[numberMap];
    std::unique_ptr<Spawner> vectors[numberMap];
    ASSERT_EQ(creation(&vectors[0],&maps[0]), true);

    TileMap map,teleport,safezone;
    sf::RectangleShape player(sf::Vector2f(tilesetResolution, tilesetResolution));
    sf::View view1(sf::Vector2f (0.0f,0.0f),sf::Vector2f (viewHeigth,viewHeigth));
    Hud hud(1);
    Achievements achievements(*hero,window,view1);
    ASSERT_EQ (achievements.load(),true);
    Textviewer objectInteraction(window.getSize().y/5,window.getSize().x,128,viewHeigth);
    ASSERT_EQ (game.initialize(*hero,mapIndex,tutorialItem,tutorialSafezone,tutorialTeleport,HudBarsHeigth,numberMap,map/*,object*/,teleport,safezone,hud,view1,player,
                               playerTexture,tilesetResolution,&maps[0],&vectors[0]), true);

    Animation animationPlayer(&playerTexture,sf::Vector2u (4,4),0.2);

    ASSERT_EQ (map.loadMap("assets/Textures-16.png", sf::Vector2u(tilesetResolution, tilesetResolution), *maps[mapIndex], maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight()),true);

    while (window.isOpen()) {

        while (window.isOpen()) {

            TileMap object;
            ASSERT_EQ (object.loadTexture("assets/potions.png"), true);
            staminaUsed=0;
            teleportText=false;
            itemText=false;
            makeText=objectInteraction.checker(*vectors[mapIndex],*hero,itemText,safezoneText,teleportText,tutorialSafezone,
                                               tutorialItem);

            deltaTime=clock.restart().asSeconds();
            hero->setGameTime(hero->getGameTime()+0.001);
            ResizeView(window,view1,viewHeigth);
            eventControl=events.event(&window,&saves[0],&names[0],&savesVec[0],*hero,tutorialItem,tutorialSafezone,tutorialTeleport,mapIndex,numberMap,game,bossNumber,monsterNumber,objectNumber,safezoneNumber,Game,map,object,teleport,safezone,&vectors[0],&maps[0]) ;

            switch (eventControl) {
                case 1:
                    window.close();
                    break;
                case 2:
                    ASSERT_EQ(map.loadMap("assets/Textures-16.png", sf::Vector2u(tilesetResolution, tilesetResolution), *maps[mapIndex], maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight()),true);
                    hero->setposX(vectors[mapIndex]->getTeleports()[0]->getposX());
                    hero->setposY(vectors[mapIndex]->getTeleports()[0]->getposY());
                    tutorialTeleport=true;
                    break;

                default:
                    break;
            }

            object.loaditem( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getObjectNumber(),*vectors[mapIndex]);
            teleport.loadTeleport( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getBossNumber(),*vectors[mapIndex]);
            safezone.loadSafezone( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getSafezoneNumber(),*vectors[mapIndex]);

            staminaUsed+=game.playerMovementUpdater(*hero,*maps[mapIndex],*vectors[mapIndex],player,tilesetResolution,run,state);
            hero->stamUse(staminaUsed);
            hero->recoverStam((0.5));
            player.setPosition(hero->getposX()*tilesetResolution,hero->getposY()*tilesetResolution);
            animationPlayer.updatePlayer(deltaTime,run,state);
            player.setTextureRect(animationPlayer.getUvRect());

            ASSERT_EQ (draw(*hero,view1,player,hud,objectInteraction,map,object,teleport,safezone), true);
            sf::sleep((sf::milliseconds(120)));
        }
    }
    Game.stop();
}
