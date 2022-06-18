//
// Created by tommy on 16/06/2022.
//

#include "Object.h"
void Object::move(int x, int y) {
    if (x > movements ||x<-movements)
        x = movements;
    if (y > movements||y<-movements)
        y = movements;
    posX += x;
    posY += y;
}

Object::Object(int movements, int posX, int posY, std::string name):movements(movements),
posX(posX),posY(posY),name(name) {
}
