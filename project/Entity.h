//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_ENTITY_H
#define MAIN_ENTITY_H
#include "Object.h"

 class Entity : public virtual Object  {

public:

     virtual ~Entity() { }

     virtual void behaviour()=0;
     virtual void tracking()=0;
     virtual void fight()=0;
     virtual void move(int x, int y)=0;
     virtual void run(int x,int y)=0;
     int getHp() const;
     void receiveDamage(int damage);
     void setHp(int hp);
     float getPreviousPos() const;
     void setPreviousPos(float previousPos);

 protected:
    float previousPos=0;
    int hp=0;
};


#endif //MAIN_ENTITY_H
