//
// Created by tommy on 28/07/2022.
//

#ifndef MAIN_ACHIEVEMENTS_H
#define MAIN_ACHIEVEMENTS_H
#include"Observer.h"
#include "Mario.h"
#include "Textviewer.h"
#include <SFML/Audio.hpp>
#include <unistd.h>
class Achievements: public Observer{
public:
    Achievements(Mario &s,sf::RenderWindow &window,sf::View &view1);
    ~Achievements();
    virtual void update(Subject *subjectChange) override;
    void draw();
    bool load();
private:
    sf::RenderWindow *window;
    sf::View *view;
    sf::Music achievementMusic;
    Mario *_subject;
    bool immortal=false;
    bool sonic=false;
    bool godSlayer=false;
    bool oldMan=false;
    bool rickSanchez=false;
    bool cargo=false;
    bool wanderer=false;
    bool lionheart=false;
    bool undead=false;


};


#endif //MAIN_ACHIEVEMENTS_H
