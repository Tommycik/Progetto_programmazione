//
// Created by tommy on 08/07/2022.
//

#include "Menu.h"

Menu::Menu(sf::RenderWindow *window) {
    background.setSize(sf::Vector2f (window->getSize().x,window->getSize().y));
    background.setPosition(0,0);

    play.setSize(sf::Vector2f (window->getSize().x/4,window->getSize().y/7));
    play.setPosition(0+window->getSize().x/2.7,0+play.getSize().y*3);

    newGame.setSize(sf::Vector2f (window->getSize().x/4,window->getSize().y/7));
    newGame.setPosition(0+window->getSize().x/2.7,play.getPosition().y+newGame.getSize().y*1.5);

    quit.setSize(sf::Vector2f (window->getSize().x/4,window->getSize().y/7));
    quit.setPosition(0+window->getSize().x/2.7,newGame.getPosition().y+quit.getSize().y*1.5);

}

bool Menu::load() {

    if(!resume.loadFromFile("assets/ContinueButton.png"))
        return false;

    resume.setSmooth(false);

    if(!restart.loadFromFile("assets/NewgameButton.png"))
        return false;

    restart.setSmooth(false);

    if(!exit.loadFromFile("assets/QuitButton.png"))
        return false;

    exit.setSmooth(false);

    if(!back.loadFromFile("assets/2cdnIK.png"))
        return false;

    background.setTexture(&back);
    play.setTexture(&resume);
    newGame.setTexture(&restart);
    quit.setTexture(&exit);

    if (!menu.openFromFile("assets/menu.wav"))
        return false;

    menu.setVolume(50.f);
    menu.setLoop(true);
    return true;
}

bool Menu::show(sf::RenderWindow *window,int &numberMap,std::string *saves,std::string *savesVec) {
    menu.play();

    bool go=false;
    while(go==false){
        sf::Event button;
        while (window->pollEvent(button))
        {
            switch (button.type){

                case sf::Event::Closed:
                    window->close();
                    menu.stop();
                    return true;
                    break;

                case sf::Event::KeyPressed:
                    if (button.key.code == sf::Keyboard::Escape){
                        window->close();
                        menu.stop();
                        return true;

                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if ((sf::Mouse::getPosition(*window).x >= 0+window->getSize().x/2.7
                         && sf::Mouse::getPosition(*window).y >=0+(window->getSize().y/7)*3+(window->getSize().y/7)*1.5+(window->getSize().y/7)*1.5
                         && sf::Mouse::getPosition(*window).x <= 0+window->getSize().x/2.7+window->getSize().x/4
                         && sf::Mouse::getPosition(*window).y <= 0+(window->getSize().y/7)*3+(window->getSize().y/7)*1.5+(window->getSize().y/7)*1.5+window->getSize().y/7)){

                        window->close();
                        menu.stop();
                        return true;

                    }

                    if ((sf::Mouse::getPosition(*window).x >= 0+window->getSize().x/2.7
                         && sf::Mouse::getPosition(*window).y >=0+(window->getSize().y/7)*3
                         && sf::Mouse::getPosition(*window).x <= 0+window->getSize().x/2.7+window->getSize().x/4
                         && sf::Mouse::getPosition(*window).y <= 0+(window->getSize().y/7)*3+window->getSize().y/7)){
                        go=true;
                    }



                    if ((sf::Mouse::getPosition(*window).x >= 0+window->getSize().x/2.7
                         && sf::Mouse::getPosition(*window).y >=0+(window->getSize().y/7)*3+(window->getSize().y/7)*1.5
                         && sf::Mouse::getPosition(*window).x <= 0+window->getSize().x/2.7+window->getSize().x/4
                         && sf::Mouse::getPosition(*window).y <= 0+(window->getSize().y/7)*3+(window->getSize().y/7)*1.5+window->getSize().y/7)){

                        for(int i=0;i<numberMap;i++){

                            try {
                                on.open(savesVec[i].c_str());
                                on.close();
                                remove(savesVec[i].c_str());
                            } catch (std::ios_base::failure& e) {}

                            try {

                                on.open(saves[i].c_str());
                                on.close();
                                remove(saves[i].c_str());
                            } catch (std::ios_base::failure& e) {}
                        }

                        try {

                            on.open("playerSave/save.txt");
                            on.close();
                            remove("playerSave/save.txt");
                        } catch (std::ios_base::failure& e) {}
                        go=true;

                    }
                    break;
                default:
                    break;
            }}
        window->clear();
        window->draw(background);
        window->draw(play);
        window->draw(newGame);
        window->draw(quit);
        window->display();}

    menu.stop();
    return false;
}

