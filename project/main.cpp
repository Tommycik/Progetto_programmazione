
#include "Animation.h"
#include "Menu.h"
#include "Events.h"
#include "Achievements.h"
#include "SkillManager.h"


void ResizeView(const sf::RenderWindow &window, sf::View &view,float viewHeigth) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(viewHeigth * aspectRatio, viewHeigth);
}

int main() {

    const int viewHeigth = 300;
    int numberMap=6;
    if(numberMap<1)
        numberMap=1;

    int monsterNumber=20;
    if(monsterNumber<5)
        monsterNumber=5;

    int objectNumber=15;
    if(objectNumber<10)
        objectNumber=10;

    int safezoneNumber=3;
    if(safezoneNumber<2)
        safezoneNumber=2;

    int bossNumber=1;
    if(bossNumber!=1)
        bossNumber=1;

    int minRooms=(bossNumber+safezoneNumber+objectNumber+monsterNumber)/2+bossNumber;

    if((bossNumber+monsterNumber+objectNumber+safezoneNumber)%2!=0)
        minRooms+=(bossNumber+monsterNumber+objectNumber+safezoneNumber)%2;
    minRooms++;
    if(minRooms<10)
        minRooms+=10;
    const unsigned int tilesetResolution=16;
    int mapIndex=0;

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

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "try"/*,sf::Style::Fullscreen*/);
    window.setFramerateLimit(60);

    sf::Music Game;
    if (!Game.openFromFile("assets/gioco.wav"))
        return -1; // error

    Game.setVolume(50.f);
    Game.setLoop(true);

    Menu menu(&window);
    if(!(menu.load())){
        return -1;
    }
    if(menu.show(&window,numberMap,&saves[0],&savesVec[0])){
        return -1;
    }
    Game.play();

    World game;
    bool tutorialItem=false,tutorialSafezone=false,tutorialTeleport=false;
    long oldseed=0;

    std::unique_ptr<Dungeonarea> maps[numberMap];
    std::unique_ptr<Spawner> vectors[numberMap];
    std::unique_ptr<Mario> hero;
    hero=std::make_unique<Mario>(100, 1, 0, 0,40,2,0);

    game.creation(*hero,monsterNumber,objectNumber,safezoneNumber,bossNumber,numberMap,oldseed,minRooms,mapIndex,tutorialItem,tutorialSafezone,tutorialTeleport,
            &saves[0],&names[0],&savesVec[0],&vectors[0],&maps[0]);
    sf::RectangleShape player(sf::Vector2f(tilesetResolution, tilesetResolution));
    sf::Texture playerTexture;
    sf::View view1(sf::Vector2f (0.0f,0.0f),sf::Vector2f (viewHeigth,viewHeigth));
    TileMap map,teleport,safezone,object,skill,obstacles,boss;
    Achievements achievements(*hero,window,view1);
    if(!achievements.load())
        return -1;
    SkillManager skillManager(game,skill);
    Hud hud(1);
    Textviewer objectInteraction(128,view1.getSize().x,view1.getSize().y/6,128);
    int HudBarsHeigth=14;

    if(!game.initialize(*hero,mapIndex,tutorialItem,tutorialSafezone,tutorialTeleport,HudBarsHeigth,numberMap,map,object,teleport,safezone,hud,view1,player,
                        playerTexture,tilesetResolution,&maps[0],&vectors[0])){
        return -1;
    }
    int state=0;
    bool run=false;
    float staminaUsed=0;
    bool makeText=false,teleportText=false,itemText=false,safezoneText=false;
    sf::Clock clock;
    float deltaTime=0.0f;
    int eventControl=0;
    Events events;
    Animation animationPlayer(&playerTexture,sf::Vector2u (4,4),0.2);
    if (!map.loadMap("assets/Textures-16.png", sf::Vector2u(tilesetResolution, tilesetResolution), *maps[mapIndex], maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight())){
        return -1;
    }
    bool change=false;
    while (window.isOpen()) {

        while (window.isOpen()) {

            change=false;
            staminaUsed=0;
            teleportText=false;
            itemText=false;
            makeText=objectInteraction.checker(*vectors[mapIndex],*hero,itemText,safezoneText,teleportText,tutorialSafezone,
                                               tutorialItem);

            deltaTime=clock.restart().asSeconds();
            hero->setGameTime(hero->getGameTime()+0.001);
            ResizeView(window,view1,viewHeigth);
            eventControl=events.event(&window,&names[0],&savesVec[0],*hero,tutorialItem,tutorialSafezone,tutorialTeleport,mapIndex,numberMap,game,Game,map,object,teleport,safezone,&vectors[0]) ;

            int count=0;
            bool found=false;
            switch (eventControl) {
                case 1:
                    window.close();
                    break;

                case 2:
                    if (!map.loadMap("assets/Textures-16.png", sf::Vector2u(tilesetResolution, tilesetResolution), *maps[mapIndex], maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight())){
                        std::cout<<"errore caricamento mappa";
                        return -1;
                    }
                    for(auto &gc:vectors[mapIndex]->getTeleports()){
                        if(gc->isActivated()){
                            found=true;
                            break;
                        }
                        count++;
                    }
                    if(found){
                        hero->setposX(vectors[mapIndex]->getTeleports()[count]->getposX());
                        hero->setposY(vectors[mapIndex]->getTeleports()[count]->getposY());
                    }else{

                        float startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 2));
                        float startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 2));
                        while(!(findFreeMapTile(startX, startY, *maps[mapIndex],&vectors[mapIndex]->getBosses(),&vectors[mapIndex]->getItems(),&vectors[mapIndex]->getEnemies(),&vectors[mapIndex]->getSafezones()))){
                            startX = maps[mapIndex]->getRand(0, (maps[mapIndex]->getWidth() - 2));
                            startY = maps[mapIndex]->getRand(0, (maps[mapIndex]->getHeight() - 2));
                        }
                        hero->setposX(startX);
                        hero->setposY(startY);
                    }
                    tutorialTeleport=true;
                    change=true;
                    break;

                default:
                    break;
            }
            staminaUsed+=game.Updater(*hero,*maps[mapIndex],*vectors[mapIndex],player,run,state);
            obstacles.loadEnemy( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getMonsterNumber(),*vectors[mapIndex],change);
            object.loaditem( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getObjectNumber(),*vectors[mapIndex]);
            teleport.loadTeleport( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getBossNumber(),*vectors[mapIndex]);
            safezone.loadSafezone( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getSafezoneNumber(),*vectors[mapIndex]);
            //boss.loadBoss(sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getBossNumber(),*vectors[mapIndex],change);
            hero->stamUse(staminaUsed);
            hero->recoverStam();
            player.setPosition(hero->getposX()*tilesetResolution,hero->getposY()*tilesetResolution);
            animationPlayer.updatePlayer(deltaTime,run,state);
            player.setTextureRect(animationPlayer.getUvRect());
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
           // window.draw(boss);
            hud.hudSow(*hero,&window,tilesetResolution,HudBarsHeigth,view1);
            float previousHp=hero->getHp();
            if(!makeText){
                hero->notify();
            }
            if(previousHp!=hero->getHp()){
                goto respawn;
            }
            objectInteraction.show(window,view1,makeText,itemText,tutorialItem,safezoneText,tutorialSafezone,teleportText,tutorialTeleport);
            window.display();
            sf::sleep((sf::milliseconds(120)));
        }
    }
    Game.stop();
    return 0;
}