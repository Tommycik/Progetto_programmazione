//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_ENTITY_H
#define MAIN_ENTITY_H
#include "Object.h"
#include "Skills.h"

class Entity : public Object  {

public:

    virtual void fight();
    virtual void run(int x,int y);
    int getHp() const;
    void receiveDamage(int damage);
    void setHp(int hp);

protected:

    int hp=0;
};


#endif //MAIN_ENTITY_H
