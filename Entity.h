//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_ENTITY_H
#define MAIN_ENTITY_H
#include "Object.h"

class Entity: public ::Object{
public:
    Entity();
    explicit Entity(int hp,int movements, int posX,int posY,std::string name);

    //virtual int fight()
    int getHp() const;

    void setHp(int hp);

protected:
    int hp;
};


#endif //MAIN_ENTITY_H
