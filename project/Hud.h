//
// Created by tommy on 19/06/2022.
//

#ifndef MAIN_HUD_H
#define MAIN_HUD_H
#include "Mario.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <sstream>
#include <iostream>

class Hud{
public:

    Hud(int thickness=1);

    bool hudSetter(Mario &player,int tilesetResolution,int &HudBarsHeigth);
    bool hudSow(Mario &hero,sf::RenderWindow *window,int tilesetResolution,int &HudBarsHeigth,sf::View &view1);

private:

    int thickness=1;
    std::stringstream ss;
    sf::RectangleShape life;
    sf::RectangleShape stamina;
    sf::RectangleShape potionIcon;
    sf::Texture hpBar,staminaBar,potion;
    sf::Font myFont;
    sf::Text Potion;
};


#endif //MAIN_HUD_H
