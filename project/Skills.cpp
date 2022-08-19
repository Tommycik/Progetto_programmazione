//
// Created by tommy on 16/06/2022.
//

#include "Skills.h"

void Skills::tracking(Entity &target) {}

void Skills::behaviour(Entity &target) {

}

void Skills::move(float x, float y) {

}

bool Skills::isOstile() const {
    return ostile;
}

bool Skills::isOutOfRange(int posX, int posY, int initialX, int initialY) {

    if (abs(posX - startX) +(abs(posY - startY) >= this->range))
        return true;

    return false;
}


void Skills::run(float x, float y) {

}

Entity *Skills::getTarget() const {
    return target;
}

void Skills::fight() {

}

bool Skills::isTargetLost() const {
    return targetLost;
}
void Skills::targetSearch(std::vector<std::unique_ptr<Boss>> &bosses,std::vector<std::unique_ptr<Obstacle>> &enemies,Entity &mario) {

    int minDistance=1000;
    if(this->ostile==false){
        for(auto &gc:enemies){
            if(gc->isFixed()==false&&gc->getHp()>0){
                if(minDistance>l2Distance(*this,gc->getposX(),gc->getposY())){
                    minDistance=l2Distance(*this,gc->getposX(),gc->getposY());
                    target=&(*gc);
                }
            }

        }
        for(auto &gc:bosses){

            if(gc->getHp()>0){
                if(minDistance>l2Distance(*this,gc->getposX(),gc->getposY())){
                    minDistance=l2Distance(*this,gc->getposX(),gc->getposY());
                    target=&(*gc);
                }
            }

        }
        if(minDistance>range){
            for(auto &gc:enemies){
                if(gc->isFixed()==true&&gc->getHp()>0){
                    if(minDistance>l2Distance(*this,gc->getposX(),gc->getposY())){
                        minDistance=l2Distance(*this,gc->getposX(),gc->getposY());
                        target=&(*gc);
                    }
                }
            }
        }
        if(minDistance<=range){
            targetFound=true;
        }else{
            target= nullptr;
            damage=0;
        }
    }

}

float Skills::getRadius() const {
    return radius;
}


