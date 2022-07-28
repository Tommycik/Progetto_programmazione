//
// Created by tommy on 28/07/2022.
//

#include "Achievements.h"


Achievements::Achievements (Mario &s,sf::RenderWindow &window,sf::View &view1)
{
    this->window=&window;
    this->view=&view1;
    _subject = &s;
    _subject->attach(this);

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

void Achievements::draw ()
{

    //todo dopo 3-5 secondi di delta time si toglie il testo
    Textviewer Achievement(window->getSize().y/5,window->getSize().x/5,128,300);
    if(_subject->getMaxHp()>=1000&&(!immortal)){
        immortal=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,Immortal","Reach 1000 health",window,*view,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getMaxStam()>=200&&(!sonic)){
        sonic=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,Sonic","Reach 200 stamina",window,*view,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getBossKilled()>=10&&(!godSlayer)){
        godSlayer=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,GodSlayer","Kill 10 or more bosses",window,*view,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getGameTime()>10&&(!oldMan)){
        oldMan=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,OldMan","You have played for quite a while",window,*view,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getTeleported()>=1&&(!rickSanchez)){
        rickSanchez=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,RickSanchez","Teleport 30 or more times",window,*view,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getPotionTaken()>=1&&(!cargo)){
        cargo=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,Cargo","Pick-up 50 or more potion",window,*view,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getDistanceWalked()>=10&&(!wanderer)){
        wanderer=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,Wanderer","Walk more than 1000 meters ",window,*view,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getSafezoneUsed()>=1&&(!lionheart)){
        lionheart=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,Lionheart","Use a safezone 20 or more times",window,*view,
                             false);
        window->display();
        sleep(5);
    }
    if(_subject->getDeaths()>=100&&(!undead)){
        undead=true;
        Achievement.blackBox(view->getCenter().x-(view->getSize().x/4),view->getCenter().y+(view->getSize().y/6),"Achievement unlocked,Undead","Die 100 or more times,you must be having fun",window,*view,
                             false);
        window->display();
        sleep(5);
    }
 window->clear();
}

bool Achievements::load() {
    if (!this->achievementMusic.openFromFile("assets/menu.wav"))
    return false;

    this->achievementMusic.setVolume(50.f);
    this->achievementMusic.setLoop(true);
    return true;
}
