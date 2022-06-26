//
// Created by tommy on 18/06/2022.
//

#ifndef MAIN_TEMPLATE_H
#define MAIN_TEMPLATE_H

#include <cstdlib>
#include "Dungeonarea.h"
#define VERBOSE
template <typename T, typename U>

 int l1Distance(const T &p, const U &q) {
    int distance = abs(p.getposX() - q.getposX()) + abs(p.getposY() - q.getposY());
    return distance;
}
template <typename T>
int l2Distance(const T &p, const int &x,const int &y) {
    int distance = abs(p.getposX() - x) + abs(p.getposY() - y);
    return distance;
}



template<typename u,typename c,typename d,typename s>
bool checkEnemyPositions(int &x, int &y,u Object1= nullptr, c Object2= nullptr, d Object3= nullptr,
                         s Object4= nullptr){
    if (Object1) {
        for (auto gc : *Object1) {
            if(gc->getHp()>0){
                if (gc->getposY() == y && gc->getposX() == x)
                    return false;
            }

        }
    }
    if (Object2) {
        for (auto gc : *Object2) {
            if(gc->isTaken()==false){
                if (gc->getposY() == y && gc->getposX() == x)
                    return false;
            }

        }
    }
    if (Object3) {
        for (auto gc : *Object3) {
            if(gc->getHp()>0){
            if (gc->getposY() == y && gc->getposX() == x)
                return false;
        }
    }}
    if (Object4) {//todo una volta creata classe teleport va mossa la condizione che se è attivo non ci si può camminare
        for (auto gc : *Object4) {
            if (gc->getposY() == y && gc->getposX() == x)
                return false;
        }
    }return true;
}

template <typename T,typename u,typename c,typename d,typename s,typename f>
bool isLegalMove(const T &object, int dX, int dY,f  &map, u* Object1= nullptr, c* Object2= nullptr, d* Object3= nullptr,
s* Object4= nullptr) {
int newX = object.getposX() + dX;
int newY = object.getposY() + dY;
// bool enemyPos = checkEnemyPositions(newX, newY, enemies);
return (

checkEnemyPositions(newX,newY,Object1,Object2,Object3,Object4)&&map.isLegalCell(newX, newY, map) );}

/*template<typename T,typename u,typename c,typename d,typename s>//todo aggiungere altri due oggetti
bool findFreeMapTile(int &x, int &y, T &map, u* Object1= nullptr, c* Object2= nullptr, d* Object3= nullptr,
                      s* Object4 = nullptr) {
    for (int i = x; i < map.getWidth(); i++) {
        for (int j = y; j < map.getHeight(); j++) {
            if (map.getcell(i,j).getType() == TileType::floor) {
#ifdef VERBOSE

                std::cout << "# floor";
#endif
                x = i;
                y = j;
                // additional check
                if (Object1) {
                    for (auto gc : *Object1) {
                        if (gc->getposY() == y && gc->getposX() == x)
                            return false;
                    }
                }
                if (Object2) {
                    for (auto gc : *Object2) {
                        if (gc->getposY() == y && gc->getposX() == x)
                            return false;
                    }
                }
                if (Object3) {
                    for (auto gc : *Object3) {
                        if (gc->getposY() == y && gc->getposX() == x)
                            return false;
                    }
                }
                if (Object4) {
                    for (auto gc : *Object4) {
                        if (gc->getposY() == y && gc->getposX() == x)
                            return false;
                    }

            } return true;
        }
    }

}return false;}*/





#endif //MAIN_TEMPLATE_H
