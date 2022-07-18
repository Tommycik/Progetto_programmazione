
#include "Animation.h"
#include "Textviewer.h"
#include "Menu.h"
#include "Events.h"
#include <memory>

//todo skill e enum class per ogni abilità
//todo ignori nemici e boss morti
//todo implementare skills con le varie texture(stessa cosa con nemici e boss)
//todo implementare oggetti paesaggio causali(alberi,ceppi,sassi ,pozzi,cartelli.....)

void ResizeView(const sf::RenderWindow &window, sf::View &view,int viewHeigth) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(viewHeigth * aspectRatio, viewHeigth);
}

int main() {

    const int viewHeigth = 300;
    int numberMap=6;
    int monsterNumber=15;
    int objectNumber=20;
    int safezoneNumber=5;
    int bossNumber=1;
    float tilesetResolution=16;
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

    numberMap=names->size();

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "try",sf::Style::Fullscreen);
    window.setFramerateLimit(100);



    sf::Music Game;
    if (!Game.openFromFile("assets/gioco.wav"))
        return -1; // error

    Game.setVolume(50.f);
    Game.setLoop(true);


    Menu menu(&window);

    if(!(menu.load()))
        return false;

    if(menu.show(&window,numberMap,&saves[0],&savesVec[0])==true){

        return 1;
    }


    Dungeonarea *maps[numberMap];
    Game.play();

    bool playerReboot=false;
    std::ifstream in;
    long oldseed=0;

    try {
        for(int i=0;i<numberMap;i++){

            maps[i] = new Dungeonarea(oldseed, 450, 450, 15, 15,30,30, i, 50, 300, 400, 400, names[i], saves[i]);
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

    Spawner *vectors[numberMap];
    for(int i=0;i<numberMap;i++) {
        vectors[i]=new Spawner(false,*maps[i],monsterNumber,objectNumber,safezoneNumber,bossNumber);
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

    World game;
    bool tutorialItem=false,tutorialSafezone=false,tutorialTeleport=false;

    Mario* hero;
    hero = new Mario(100, 1, 0, 0,40,2,0);

    sf::RectangleShape player(sf::Vector2f(tilesetResolution, tilesetResolution));
    sf::Texture playerTexture;
    sf::View view1(sf::Vector2f (0.0f,0.0f),sf::Vector2f (viewHeigth,viewHeigth));
    Hud hud(1);
    TileMap map,object,teleport,safezone;
    Textviewer objectInteraction(window.getSize().y/5,window.getSize().x,128,viewHeigth);

    int HudXOffset=-268;
    int HudYOffset =-147;
    int HudBarsHeigth=14;

    if(!game.initialize(*hero,mapIndex,tutorialItem,tutorialSafezone,tutorialTeleport,HudBarsHeigth,numberMap,map,object,teleport,safezone,hud,view1,player,
                        playerTexture,tilesetResolution,&maps[0],&vectors[0])){

        game.destroyer(numberMap,*hero,&vectors[0],&maps[0]);
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
    while (window.isOpen()) {


        while (window.isOpen()) {
            staminaUsed=0;
            teleportText=false;
            itemText=false;
            makeText=objectInteraction.checker(*vectors[mapIndex],*hero,itemText,safezoneText,teleportText,tutorialSafezone,
                                               tutorialItem);

            deltaTime=clock.restart().asSeconds();
            ResizeView(window,view1,viewHeigth);

            eventControl=events.event(&window,&saves[0],&names[0],&savesVec[0],*hero,tutorialItem,tutorialSafezone,tutorialTeleport,mapIndex,numberMap,game,bossNumber,monsterNumber,objectNumber,safezoneNumber,tilesetResolution,Game,map,object,teleport,safezone,player,&vectors[0],&maps[0]) ;
            switch (eventControl) {
                case 1:
                    return 1;
                    break;
                case-1:
                    std::cout<<"errore caricamento mappa";
                    game.destroyer(numberMap,*hero,&vectors[0],&maps[0]);
                    return -1;
                    break;

                default:
                    break;
            }

            sf::sleep((sf::milliseconds(120)));
            staminaUsed+=game.playerMovementUpdater(*hero,*maps[mapIndex],*vectors[mapIndex],player,tilesetResolution,run,state);
            hero->stamUse(staminaUsed);
            hero->recoverStam((0.5));
            animationPlayer.updatePlayer(deltaTime,run,state);
            player.setTextureRect(animationPlayer.getUvRect());

            window.clear();
            view1.setCenter(player.getPosition());
            window.setView(view1);
            window.draw(map);
            window.draw(teleport);
            window.draw(player);
            window.draw(safezone);
            window.draw(object);
            hud.hudSow(*hero,&window,tilesetResolution,HudBarsHeigth,view1);
            objectInteraction.show(window,view1,makeText,itemText,tutorialItem,safezoneText,tutorialSafezone,teleportText,tutorialTeleport);
            window.display();
        }
    }

    game.destroyer(numberMap,*hero,&vectors[0],&maps[0]);
    Game.stop();
    return 0;
}