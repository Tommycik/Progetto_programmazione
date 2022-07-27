//
// Created by tommy on 16/06/2022.
//

#include "Iceslide.h"

void Iceslide::slide(int &posX, int &posY,int x,int y,int movements) {
   posX+=movements*x*3;
    posY+=movements*y*3;
}

