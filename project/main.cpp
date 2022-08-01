
#include "Animation.h"
#include "Menu.h"
#include "Events.h"
#include "Achievements.h"

 //todo implementare  line enemies
 //todo mettere effetto audio achievement e sistemare le soglie
 //todo per i vari vettori implementare erase invece di lascare i vari oggetti presi o i nemici morti;
//todo skill e enum class per ogni abilità
//todo ignori nemici e boss morti
//todo implementare skills con le varie texture(stessa cosa con nemici e boss)
//todo implementare oggetti paesaggio causali(alberi,ceppi,sassi ,pozzi,cartelli.....)
//todo differenziare mappe in possibilità stanze e loro dimensione
void ResizeView(const sf::RenderWindow &window, sf::View &view,int viewHeigth) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(viewHeigth * aspectRatio, viewHeigth);
}

int main() {

    const int viewHeigth = 300;
    int numberMap=6;
    if(numberMap<1)
        numberMap=1;

    int monsterNumber=15;
    if(monsterNumber<1)
        monsterNumber=1;

    int objectNumber=10;
    if(objectNumber<1)
        objectNumber=1;

    int safezoneNumber=3;
    if(safezoneNumber<1)
        safezoneNumber=1;

    int bossNumber=10;
    if(bossNumber<1)
        bossNumber=1;
    int minRooms=(bossNumber+safezoneNumber+objectNumber+monsterNumber)/3+bossNumber;

    if((bossNumber+monsterNumber+objectNumber+safezoneNumber)%3!=0)
        minRooms++;
    minRooms++;
    const float tilesetResolution=16;
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
        return false;
    }
    if(menu.show(&window,numberMap,&saves[0],&savesVec[0])){
        return 1;
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
    Achievements achievements(*hero,window,view1);
    if(!achievements.load())
        return -1;
    Hud hud(1);
    TileMap map,teleport,safezone;
    Textviewer objectInteraction(window.getSize().y/5,window.getSize().x,128,viewHeigth);
    int HudBarsHeigth=14;

    if(!game.initialize(*hero,mapIndex,tutorialItem,tutorialSafezone,tutorialTeleport,HudBarsHeigth,numberMap,map/*,object*/,teleport,safezone,hud,view1,player,
                        playerTexture,tilesetResolution,&maps[0],&vectors[0])){
        return -1;
    }
    if (!map.loadMap("assets/Textures-16.png", sf::Vector2u(tilesetResolution, tilesetResolution), *maps[mapIndex], maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight())){
        return false;
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

            TileMap object;
            if (! object.loadTexture("assets/potions.png")){
                std::cout<<"errore caricamento oggetti";
                return -1;
            }
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
                    return 1;

                case 2:
                    if (!map.loadMap("assets/Textures-16.png", sf::Vector2u(tilesetResolution, tilesetResolution), *maps[mapIndex], maps[mapIndex]->getWidth(), maps[mapIndex]->getHeight())){
                        std::cout<<"errore caricamento mappa";
                        return -1;
                    }

                    hero->setposX(vectors[mapIndex]->getTeleports()[0]->getposX()); //fixme controllare teletrasporto d'arrivo
                    hero->setposY(vectors[mapIndex]->getTeleports()[0]->getposY());
                    tutorialTeleport=true;
                    break;

                default:
                    break;
            }
            object.loaditem( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getObjectNumber(),*vectors[mapIndex]);
            teleport.loadTeleport( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getBossNumber(),*vectors[mapIndex]);
            safezone.loadSafezone( sf::Vector2u(tilesetResolution, tilesetResolution),vectors[mapIndex]->getSafezoneNumber(),*vectors[mapIndex]);

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
            if(!makeText){
                hero->notify();
            }
            objectInteraction.show(window,view1,makeText,itemText,tutorialItem,safezoneText,tutorialSafezone,teleportText,tutorialTeleport);
            window.display();
        }
    }
    Game.stop();
    return 0;
}