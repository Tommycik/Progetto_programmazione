//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_ITEM_H
#define MAIN_ITEM_H

#include "Object.h"

class Item : public virtual Object {
public:

    Item(int posX, int posY, int effect);

    bool isTaken() const;

    void setTaken(bool taken);

    int getEffect() const;

    void setEffect(int effect);

private:

    bool taken = false;
    int effect = 1;
};

#endif //MAIN_ITEM_H
