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
    explicit Entity(int hp,int movements, int posX,int posY,std::string name);

    //virtual int fight()
    int getHp() const;

    void setHp(int hp);
    void run(int x,int y) {
        if (x > movements ||x<-movements)
            x = movements;
        if (y > movements||y<-movements)
            y = movements;
        posX += 2*x;
        posY += 2*y;
    }

protected:
    int hp;
};


#endif //MAIN_ENTITY_H
