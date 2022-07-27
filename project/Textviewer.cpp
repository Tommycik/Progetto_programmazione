//
// Created by tommy on 27/06/2022.
//

#include "Textviewer.h"

const std::string &Textviewer::getFont() const {
    return font;
}

void Textviewer::setFont(const std::string &font) {
    Textviewer::font = font;
}

Textviewer::Textviewer(unsigned int heigth,unsigned int length, int textDimension,int viewHeigth) : heigth(heigth),length(length),
                                                                                   textDimension(textDimension){

    box.setSize(sf::Vector2f (viewHeigth,viewHeigth/6));
    sf::Color color(0,0,0,128);
    box.setFillColor(color);
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(1);

}

bool Textviewer::blackBox(float posX,float posY,std::string text1, std::string text2,sf::RenderWindow *window,bool center ) {
    //sf::RectangleShape text(sf::Vector2f(length, heigth));

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

    if(center){
        textOne.setOrigin(textOne.getLocalBounds().width/2,textOne.getLocalBounds().height/2);
    }

    textOne.setPosition(posX,posY);
    textTwo.setPosition(posX,posY+24);
    window->draw(textOne);
    window->draw(textTwo);

    return false;
}

bool Textviewer::checker(Spawner &creator,Mario &hero, bool &itemText, bool &safezoneText, bool &teleportText,bool tutorialSafezone,bool tutorialItem) {
    bool makeText=false;
    for(auto &gc:creator.getTeleports()){
        if(l2Distance(*gc,hero.getposX(),hero.getposY())<=1&&(gc->isActivated())) {
            makeText=true;
            teleportText=true;}
    }

    if(!tutorialItem){
        for(auto &gc:creator.getItems()){
            if(l2Distance(*gc,hero.getposX(),hero.getposY())<=1&&(!gc->isTaken())) {
                makeText=true;
                itemText=true;}
        }
    }

    if(!tutorialSafezone){
        for(auto &gc:creator.getSafezones()){
            if(l2Distance(*gc,hero.getposX(),hero.getposY())<=1) {
                makeText=true;
                safezoneText=true;}
        }
    }
    return makeText;
}

void Textviewer::show(sf::RenderWindow &window,sf::View &view1, bool &makeText, bool &itemText, bool &tutorialItem, bool &safezoneText,
                      bool &tutorialSafezone, bool &teleportText, bool &tutorialTeleport) {

    if(makeText) {
        box.setPosition(view1.getCenter().x-(view1.getSize().x/4),view1.getCenter().y+(view1.getSize().y/6));
        window.draw(box);
        if(itemText){
            if(tutorialItem==false){

                this->blackBox(box.getPosition().x,box.getPosition().y,"Per raccogliere gli oggetti premi R","Per usare le pozioni premi B",&window,false);

            }
        }else if(safezoneText){
            if(tutorialSafezone==false){

                this->blackBox(box.getPosition().x,box.getPosition().y,"Hai trovato una fonte di luce","Per usarne il potere premi T",&window,false);

            }
        }else if(teleportText){
            if(tutorialTeleport){

                this->blackBox(box.getPosition().x,box.getPosition().y,"Il teletrasporto emana un'aura misteriosa...","",&window,
                               false);

            }else {

                this->blackBox(box.getPosition().x,box.getPosition().y,"Per usare il potere del teletrasporto premere P o O","",&window,
                               false);//P scorre in avanti mentre  O scorre indietro
            }
        }
    }
}
