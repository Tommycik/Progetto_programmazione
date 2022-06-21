//
// Created by tommy on 21/06/2022.
//

#include "Animation.h"




Animation::~Animation() {

}
Animation::Animation(sf::Texture* texture,sf::Vector2u imageCount,float switchTime) {//image counter è il numero di texture totali nel file

    this->imageCount=imageCount;
    this->switchTime=switchTime;
    totalTime=0.0f;
    totalTimeIdle=0.0f;
    totalTimeMovement=0.0f;
    currentImage.x=0;
    currentImage.y=0;
     turn= false;
    uvRect.width=texture->getSize().x/float(imageCount.x);
    uvRect.height=texture->getSize().y/float(imageCount.y);
}



void Animation::update(int row,float deltaTime,bool faceRight) {
    currentImage.y=row;
    totalTime+=deltaTime;
    if(totalTime<=switchTime){
        totalTime-=switchTime;
        currentImage.x++;//usando variabili float solo = renderebbe l'animazione meno fluida

        if(currentImage.x>=imageCount.x){
           currentImage.x=0;
        }
    }
    uvRect.top=currentImage.y*uvRect.height;

    if(faceRight){
        uvRect.left=currentImage.x*uvRect.width;
        uvRect.width=abs(uvRect.width);
    }else{

        uvRect.left=(currentImage.x+1)*abs(uvRect.width);
        uvRect.width=-abs(uvRect.width);
    }

}

void Animation::updatePlayer(float deltaTime, bool running,unsigned int state) {

    if(state==0){
        totalTimeMovement=0;
        totalTimeIdle+=deltaTime;
        currentImage.y=0;
        currentImage.x=0;
        if(!(totalTimeIdle<=2)){
            totalTimeIdle-=2;
            uvRect.top=currentImage.y*uvRect.height;
            if( turn==false){
                uvRect.left=currentImage.x*uvRect.width;
                uvRect.width=abs(uvRect.width);
                turn=true;}else{
                uvRect.left=(currentImage.x+1)*abs(uvRect.width);
                uvRect.width=-abs(uvRect.width);
                turn=false;
            }

        }else{
            uvRect.top=currentImage.y*uvRect.height;
            uvRect.left=currentImage.x*uvRect.width;
            uvRect.width=abs(uvRect.width);
        }
    }else{
        totalTimeMovement+=deltaTime;
        totalTimeIdle=0;
        currentImage.y=3;
        currentImage.x=1;
        if(running){
             switching=switchTime/2;
        }else{
            switching=switchTime;
        }
        if(totalTimeMovement>switching){
            totalTimeMovement-=switching;
            //usando variabili float solo = renderebbe l'animazione meno fluida

            currentImage.x++;
            if(currentImage.x>2){
                currentImage.x=1;
            }

        }
        uvRect.top=currentImage.y*uvRect.height;

        if(!(state==1)){
            uvRect.left=currentImage.x*abs(uvRect.width);
            uvRect.width=abs(uvRect.width);

        }else{

            uvRect.left=(currentImage.x+1)*abs(uvRect.width);
            uvRect.width=-abs(uvRect.width);

        }


        }

    //
    }



