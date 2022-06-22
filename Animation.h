//
// Created by tommy on 21/06/2022.
//

#ifndef MAIN_ANIMATION_H
#define MAIN_ANIMATION_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "Dungeonarea.h"

class Animation{
public:
    Animation(sf::Texture* texture,sf::Vector2u imageCount,float switchTime);
    void update(int row,float deltaTime,bool faceRight);
    void updatePlayer(float deltaTime,bool running,unsigned int state);
   ~Animation();

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float switchTime;
    float totalTimeIdle;
    float totalTime;
    float totalTimeMovement;
    bool turn;
    float switching;
public:
    sf::IntRect uvRect;
};


#endif //MAIN_ANIMATION_H
