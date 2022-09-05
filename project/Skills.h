//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_SKILLS_H
#define MAIN_SKILLS_H
#include <iostream>
#include "Obstacle.h"
#include "Boss.h"

class Skills :public  Entity{

public:

    void tracking(Entity &target) override;
    void behaviour(Entity &target) override;
    void move(float x, float y) override;
    void run(float x,float y) override;
    void fight() override;
    bool isOutOfRange(int posX, int posY,int initialX,int initialY);
    void targetSearch(std::vector<std::unique_ptr<Boss>> &bosses,std::vector<std::unique_ptr<Obstacle>> &enemies,Entity &mario);
    Entity *getTarget() const;
    bool isTargetLost() const;
    float getRadius() const;
    bool isTargetFound() const;
    void setTargetFound(bool targetFound);
    int getstartX() const{
        return startX;
    }
    void setstartX(int posX){
        Skills::startX=posX;
    }
    int getStamConsumption() const{
        return stamConsumption;
    }
    bool isOstile() const;

    int getDamage() const{
        return damage;
    }

protected:

    Entity*target;
    int damage;
    int startX;
    int startY;
    int stamConsumption;
    int range;
    bool ostile;
    bool targetLost=false;
    bool targetFound=false;
    float radius=0;
};


#endif //MAIN_SKILLS_H
