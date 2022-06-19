//
// Created by tommy on 18/06/2022.
//

#ifndef MAIN_TEMPLATE_H
#define MAIN_TEMPLATE_H

#include <cstdlib>
#include "Dungeonarea.h"
template <typename T, typename U>

int l1Distance(const T &p, const U &q) {
    int distance = abs(p.getPosX() - q.getPosX()) + abs(p.getPosY() - q.getPosY());
    return distance;
}

template <typename T,typename u>
bool isLegalMove(const T &object, int dX, int dY,u  &map) {//todo mancano i vettori
    int newX = object.getposX() + dX;
    int newY = object.getposY() + dY;
    // bool enemyPos = checkEnemyPositions(newX, newY, enemies);
    return (map.isLegalCell(newX, newY, map) );
}
template<typename T>//todo aggiungere altri due oggetti
bool findFreeMapTile(int &x, int &y, T &map/*,const u &Object1,const c &Object2*/) {
    for (int i = x; i < map.getWidth(); i++) {
        for (int j = y; j < map.getHeight(); j++) {
            if (map.getcell(i,j).getType() == TileType::floor) {
                x = i;
                y = j;
                // additional check
                /*if (gameCharacters) {
                    for (auto gc : *gameCharacters) {
                        if (gc->getPosY() == y && gc->getPosX() == x)
                            return false;
                    }
                }*/
                return true;
            }
        }
    }
    return false;
}





#endif //MAIN_TEMPLATE_H
