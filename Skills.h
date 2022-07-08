//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_SKILLS_H
#define MAIN_SKILLS_H
#include <iostream>
#include "Object.h"
//manca l'override di move ed il movimento della skill
class Skills:public Object{
public:

    int getUnlocked() const{
        return unlocked;
    }
    void setUnlocked(bool usable){
        Skills::unlocked=usable;
    }
    int getstartX() const{
        return startX;
    }
    void setstartX(int posX){
        Skills::startX=posX;
    }
    int getStamConsumption() const{
        return stamConsumption;
    }
    int getDamage() const{
        return damage;
    }
    bool isOutOfRange(int posX, int posY,int initialX,int initialY,int maxRange) {

            if (abs(posX - startX) +(abs(posY - startY) == maxRange))
                return true;
        return false;
    }

protected:
    int damage;
    int startX;
    int startY;
    int stamConsumption;
    int range;
    bool unlocked= false;
};


#endif //MAIN_SKILLS_H
