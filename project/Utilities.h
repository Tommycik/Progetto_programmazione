//
// Created by tommy on 18/06/2022.
//

#ifndef MAIN_UTILITIES_H
#define MAIN_UTILITIES_H
#include <cstdlib>
#include "Dungeonarea.h"

template <typename T, typename U>
int l1Distance(const T &p, const U &q) {
    int distance = abs(p.getposX() - q.getposX()) + abs(p.getposY() - q.getposY());
    return distance;
}

template <typename T>
int l2Distance(const T &p, const float &x,const float &y) {
    int distance = abs(p.getposX() - x) + abs(p.getposY() - y);
    return distance;
}



template<typename u,typename c,typename d,typename s>
bool checkEnemyPositions(float &x, float &y,u Object1= nullptr, c Object2= nullptr, d Object3= nullptr,
                         s Object4= nullptr){
    if (Object1!= nullptr) {
        for (auto &gc : *Object1) {
            if(gc->getHp()>0){
                if (abs(gc->getposY() -y)<0.25 && abs(gc->getposX() -x)<0.25)
                    return false;
            }
        }
    }
    if (Object2!= nullptr) {
        for (auto &gc : *Object2) {
            if(gc->isTaken()==false){
                if (abs(gc->getposY() -y)<0.25 && abs(gc->getposX() -x)<0.25)
                    return false;
            }
        }
    }
    if (Object3!= nullptr) {
        for (auto &gc : *Object3) {
            if(gc->getHp()>0){
                if (abs(gc->getposY() -y)<0.25 && abs(gc->getposX() -x)<0.25)
                    return false;
            }
        }
    }
    if (Object4!= nullptr) {
        for (auto &gc : *Object4) {
            if (abs(gc->getposY() -y)<0.25 && abs(gc->getposX() -x)<0.25)
                return false;
        }
    }
    return true;
}

template <typename T,typename u,typename c,typename d,typename s,typename f>
bool isLegalMove(const T &object, float dX, float dY,f  &map, u* Object1= nullptr, c* Object2= nullptr, d* Object3= nullptr,
                 s* Object4= nullptr) {
    float newX = object.getposX() + dX;
    float newY = object.getposY() + dY;
// bool enemyPos = checkEnemyPositions(newX, newY, enemies);
    return (checkEnemyPositions(newX,newY,Object1,Object2,Object3,Object4)&&map.getPassable(newX, newY));}

template <typename T>
bool isLegalDamage(int x,int y,T* Object){

    if(Object!= nullptr){


        for(auto gc: *Object) {
            if(x==gc->getposX && y==gc->getposY)
                return true;

        }
    }
    return false;
}//todo implementare il controllo danni nei metodi behaviour e usare come controllo il metodo distanza


template<typename T,typename u,typename c,typename d,typename s>
bool findFreeMapTile(int &x, int &y, T &map, u* Object1= nullptr, c* Object2= nullptr, d* Object3= nullptr,
                     s* Object4 = nullptr) {
    bool found=false;
    for (int i = x; i < map.getWidth(); i++) {
        for (int j = y; j < map.getHeight(); j++) {
            if (map.getPassable(i,j)== true) {//fixme incapsulare l'informazione se è camminabile

                if(map.getSpawnPlace(i,j)==true){
                    found=true;
                    x = i;
                    y = j;

                    if (Object1!= nullptr) {
                        for (auto &gc : *Object1) {
                            if (l2Distance(*gc, x,y)<30)
                                found=false;
                        }
                    }
                    if (Object2!= nullptr) {
                        for (auto &gc : *Object2) {
                            if (l2Distance(*gc, x,y)<15)
                                found=false;
                        }
                    }
                    if (Object3!= nullptr) {
                        for (auto &gc : *Object3) {
                            if (l2Distance(*gc, x,y)<15)
                                found=false;
                        }
                    }
                    if (Object4!= nullptr) {
                        for (auto &gc : *Object4) {
                            if (l2Distance(*gc, x,y)<15)
                                found=false;
                        }
                    }
                    if(found){
                        return true;
                    }
                }

            }
        }
    }
    return false;
}





#endif //MAIN_UTILITIES_H
