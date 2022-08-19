//
// Created by tommy on 28/07/2022.
//

#include "Achievements.h"


Achievements::Achievements (Mario &hero,sf::RenderWindow &window,sf::View &view1)
{
    this->window=&window;
    this->view=&view1;
    _subject = &hero;
    _subject->attach(this);
    if(!loadAchievements()){
        saveAchievements();
    }

}

Achievements::~Achievements ()
{
    _subject->detach(this);
}

void Achievements::update (Subject *theChangedSubject)
{
    if(theChangedSubject == _subject)
        draw();
}

void Achievements::draw (){

    Textviewer Achievement(128,view->getSize().x/2,view->getSize().y/6,128);
    if(_subject->getMaxHp()>=1000&&(!immortal)){
        immortal=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,Immortal","Reach 1000 health",window,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getMaxStam()>=200&&(!sonic)){
        sonic=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,Sonic","Reach 200 stamina",window,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getBossKilled()>=5&&(!godSlayer)){
        godSlayer=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,GodSlayer","Kill 10 or more bosses",window,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getGameTime()>10&&(!oldMan)){
        oldMan=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,OldMan","You have played for quite a while",window,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getTeleported()>=30&&(!rickSanchez)){
        rickSanchez=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,RickSanchez","Teleport 30 or more times",window,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getPotionTaken()>=30&&(!cargo)){
        cargo=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,Cargo","Pick-up 30 or more potion",window,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getDistanceWalked()>=1000&&(!wanderer)){
        wanderer=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,Wanderer","Walk more than 1000 meters ",window,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getSafezoneUsed()>=20&&(!lionheart)){
        lionheart=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,Lionheart","Use a safezone 20 or more times",window,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getDeaths()>=100&&(!undead)){
        undead=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,Undead","Die 100 or more times,you must be having fun",window,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getHp()==0) {
        Textviewer death(512, view->getSize().x, view->getSize().y, 255);

        _subject->recoverHp(0);
        _subject->setDeaths(1);
        death.blackBox(view->getCenter().x - (view->getSize().x / 2), view->getCenter().y - (view->getSize().y / 2),
                       "GAME OVER", "", window,
                       true);
        window->display();
        bool wait = false;
        sleep(3);
        while (!wait) {
            sf::Event event;
            while (window->pollEvent(event)){
                if (event.type == sf::Event::KeyPressed)
                    wait = true;
            }
        }
    }
    this->saveAchievements();
}

bool Achievements::load() {
    if (!this->achievementMusic.openFromFile("assets/menu.wav"))
    return false;

    this->achievementMusic.setVolume(50.f);
    this->achievementMusic.setLoop(true);
    return true;
}

void Achievements::saveAchievements() const {
    std::ofstream out;
    out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    // try {
    out.open("playerSave/Achievement.txt",std::ios_base::trunc);
    out <<immortal << std::endl;
    out <<sonic<< std::endl;
    out <<godSlayer<< std::endl;
    out <<oldMan<< std::endl;
    out <<rickSanchez<< std::endl;
    out <<cargo<< std::endl;
    out <<wanderer<< std::endl;
    out <<lionheart<< std::endl;
    out <<undead<< std::endl;
    out.close();
}

bool Achievements::loadAchievements() {
    op.exceptions(std::ifstream::failbit);

    try {
        op.open("playerSave/Achievement.txt");
    } catch (std::ios_base::failure& e) {

        return false;
    }
   std::getline(op, fileLine);
    try {
        immortal=std::stoi(fileLine);
        std::getline(op, fileLine);
        sonic=std::stoi(fileLine);
        std::getline(op, fileLine);
        godSlayer=std::stoi(fileLine);
        std::getline(op, fileLine);
        oldMan=std::stoi(fileLine);
        std::getline(op, fileLine);
        rickSanchez=std::stoi(fileLine);
        std::getline(op, fileLine);
        cargo=std::stoi(fileLine);
        std::getline(op, fileLine);
        wanderer=std::stoi(fileLine);
        std::getline(op, fileLine);
        lionheart=std::stoi(fileLine);
        std::getline(op, fileLine);
        undead=std::stoi(fileLine);
    } catch (std::out_of_range &e) {
        throw std::out_of_range("Can not set vector tile at x: ");
    }

    op.close();
    return true;
}
