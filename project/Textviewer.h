//
// Created by tommy on 27/06/2022.
//

#ifndef MAIN_TEXTVIEWER_H
#define MAIN_TEXTVIEWER_H
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Spawner.h"

class Textviewer {

public:

    Textviewer(int textDimension,float xDimension,float yDimension,int alphaOfColor);

    bool blackBox(float posX,float posY,std::string text1,std::string text2,sf::RenderWindow *window,bool death );
    bool checker(Spawner &creator,Mario &hero,bool &itemText,bool &safezoneText,bool &teleportText,bool tutorialSafezone,bool tutorialItem);
    const std::string &getFont() const;
    void setFont(const std::string &font);
    void show(sf::RenderWindow &window,sf::View &view1,bool &makeText,bool &itemText,bool &tutorialItem,bool &safezoneText,bool &tutorialSafezone,bool &teleportText,bool &tutorialTeleport);

private:

    int heigth=0;
    int length=0;
    int textDimension=0;
    std::string font="assets/arial.ttf";
    sf::Font myTextFont;
    sf::RectangleShape box;
    std::stringstream su,sd;
    sf::Text textOne;
    sf::Text textTwo;

};


#endif //MAIN_TEXTVIEWER_H
