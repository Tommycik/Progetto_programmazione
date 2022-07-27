//
// Created by tommy on 22/06/2022.
//

#ifndef MAIN_TELEPORT_H
#define MAIN_TELEPORT_H
#include "Mario.h"

class Teleport:public virtual Object {

public:

    Teleport( int posX, int posY);

    void teleportation(Mario &hero,int finalX,int finalY);
    bool isActivated() const;
    void setActivated(bool activated);

private:

    bool activated=true;

};


#endif //MAIN_TELEPORT_H
