//
// Created by tommy on 27/06/2022.
//

#ifndef MAIN_TEXTVIEWER_H
#define MAIN_TEXTVIEWER_H
#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Textviewer {
public:
    bool blackBox(float posX,float posY,std::string text1,std::string text2,sf::RenderWindow *window );
private:
    int heigth=0;
    int length=0;
public:
    int getHeigth() const;

    void setHeigth(int heigth);

    Textviewer(int heigth, int length, int textDimension);

    int getLength() const;

    void setLength(int length);

    int getTextDimension() const;

    void setTextDimension(int textDimension);

    const std::string &getFont() const;

    void setFont(const std::string &font);

private:

    int textDimension=0;
    std::string font="../assets/arial.ttf";

};


#endif //MAIN_TEXTVIEWER_H
