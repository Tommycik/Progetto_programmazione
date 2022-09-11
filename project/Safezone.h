//
// Created by tommy on 08/07/2022.
//

#ifndef MAIN_SAFEZONE_H
#define MAIN_SAFEZONE_H

#include "Object.h"

class Safezone : public virtual Object {

public:

    Safezone(int posX, int posY);

    bool isUsed() const;

    void setUsed(bool used);

private:

    bool used = false;
};


#endif //MAIN_SAFEZONE_H
