//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_SKILLS_H
#define MAIN_SKILLS_H
#include <iostream>
#include "Entity.h"

enum class skill{
fire=0
};

//todo implementarle tramite un vettore ed usare vector erase() per cancellare le abilità a schermo da distruggere
//todo questa srà la classe che gestisce  le abilità
class Skills:public Object{

public:

    virtual void tracking() override;
    virtual void behaviour() override;
    virtual void move(int x, int y) override;
    bool isOutOfRange(int posX, int posY,int initialX,int initialY);
    skill getType() const;

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
    void setType(skill type);

    int getDamage() const{
        return damage;
    }

protected:

    int damage;
    int startX;
    int startY;
    int stamConsumption;
    int range;
    bool ostile;
    skill type=skill::fire;

};


#endif //MAIN_SKILLS_H
