//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_ENTITY_H
#define MAIN_ENTITY_H
#include "Object.h"
#include "Dungeonarea.h"
#include <time.h>
#include <iostream>
#include <random>

 class Entity : public  Object  {

public:

     virtual ~Entity() { }

     virtual void behaviour(Entity &target)=0;
     virtual void tracking(Entity &target)=0;
     virtual void fight()=0;
     virtual void move(float x, float y)=0;
     virtual void run(float x,float y)=0;
     float getHp() const;
     void receiveDamage(int damage);
     void setHp(int hp);
     int getTextureMultiplier() const;
     float getDirectX() const;
     float getDirectY() const;
     bool isChecked() const;
     void setChecked(bool checked);
     float getTimeSinceDamage() const;
     void setTimeSinceDamage(float timeSinceDamage);
     int getType() const;
     int getSkillUsed() const;

 protected:

    int skillUsed=0;
    float hp=0;
    int textureMultiplier=1;
     int oldseed=0;
     float directX=0;
     float directY=0;
     bool checked=false;
     float timeSinceDamage=0.00;
     int type=0;
};


#endif //MAIN_ENTITY_H
