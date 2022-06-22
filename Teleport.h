//
// Created by tommy on 22/06/2022.
//

#ifndef MAIN_TELEPORT_H
#define MAIN_TELEPORT_H
#include "Object.h"

class Teleport:public Object {
private:
    bool activated;
public:
    Teleport( int posX, int posY);

public:
    bool isActivated() const;

    void setActivated(bool activated);
};


#endif //MAIN_TELEPORT_H
