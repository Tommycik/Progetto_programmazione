//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_ENTITY_H
#define MAIN_ENTITY_H
#include "Object.h"
#include "Skills.h"
class Entity : public Object  {
public:
    Entity();
    explicit Entity(int hp,int movements, int posX,int posY);

    //virtual int fight()
    int getHp() const;

    void setHp(int hp);
    void run(int x,int y);

protected:
    int hp;
};


#endif //MAIN_ENTITY_H
