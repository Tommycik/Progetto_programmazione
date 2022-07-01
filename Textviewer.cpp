//
// Created by tommy on 27/06/2022.
//

#include "Textviewer.h"

int Textviewer::getHeigth() const {
    return heigth;
}

void Textviewer::setHeigth(int heigth) {
    Textviewer::heigth = heigth;
}

int Textviewer::getLength() const {
    return length;
}

void Textviewer::setLength(int length) {
    Textviewer::length = length;
}

int Textviewer::getTextDimension() const {
    return textDimension;
}

void Textviewer::setTextDimension(int textDimension) {
    Textviewer::textDimension = textDimension;
}

const std::string &Textviewer::getFont() const {
    return font;
}

void Textviewer::setFont(const std::string &font) {
    Textviewer::font = font;
}

Textviewer::Textviewer(int heigth, int length, int textDimension) : heigth(heigth),
                                                                                             length(length),
                                                                                             textDimension(
                                                                                                     textDimension){}

bool Textviewer::blackBox(float posX,float posY,std::string text1, std::string text2,sf::RenderWindow *window ) {
    //sf::RectangleShape text(sf::Vector2f(length, heigth));

    sf::Font myTextFont;
    std::stringstream su,sd;
    sf::Text textOne;
    sf::Text textTwo;
    textOne.setFont(myTextFont);
    textTwo.setFont(myTextFont);
    textOne.setFillColor(sf::Color::White);
    textOne.setCharacterSize(textDimension);//todo mettere 128 nel main
    textOne.setScale(sf::Vector2f(0.1,0.1));
    textOne.setOutlineThickness(1);
    textTwo.setFillColor(sf::Color::White);
    textTwo.setCharacterSize(textDimension);
    textTwo.setScale(sf::Vector2f(0.1,0.1));
    textTwo.setOutlineThickness(1);
    textOne.setPosition(posX,posY);
    textTwo.setPosition(posX,posY+24);
    if (!myTextFont.loadFromFile(font))
    {
        return -1;
    }

    su << text1;
    sd << text2;
    textOne.setString( su.str().c_str() );
    su.str("");
    textTwo.setString( sd.str().c_str() );
    sd.str("");
    window->draw(textOne);
    window->draw(textTwo);

    return false;
}

bool Textviewer::checker(Spawner &creator,Mario &hero, bool &itemText, bool &safezoneText, bool &teleportText,bool tutorialSafezone,bool tutorialItem) {
   bool makeText=false;
    for(auto gc:creator.getTeleports()){
        if(l2Distance(*gc,hero.getposX(),hero.getposY())<=1&&(gc->isActivated())) {
            makeText=true;
            teleportText=true;}
    }

    if(!tutorialItem){
        for(auto gc:creator.getItems()){
            if(l2Distance(*gc,hero.getposX(),hero.getposY())<=1&&(!gc->isTaken())) {
                makeText=true;
                itemText=true;}
        }
    }

    if(!tutorialSafezone){
        for(auto gc:creator.getSafezones()){
            if(l2Distance(*gc,hero.getposX(),hero.getposY())<=1) {
                makeText=true;
                safezoneText=true;}
        }
    }
    return makeText;
}
