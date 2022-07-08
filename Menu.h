//
// Created by tommy on 08/07/2022.
//

#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class Menu {
public:

    Menu(sf::RenderWindow *window);
    bool load();
    bool show(sf::RenderWindow *window,int numberMap,std::string *saves,std::string *savesVec);


private:
    sf::RectangleShape background;
    sf::RectangleShape quit;
    sf::RectangleShape newGame;
    sf::RectangleShape play;
    sf::Texture resume,restart,exit,back;
    sf::Music menu;
};


#endif //MAIN_MENU_H
