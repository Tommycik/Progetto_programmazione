//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H
#include <iostream>

class Object {
public:
    Object();
    explicit Object(int movements, int posX,int posY,std::string name);
    virtual void move(int x, int y);

void setMovements(int variation){
Object::movements=variation;
}
int getMovements()const{
    return movements;
}
    void setposX(int x){
        Object::posX=x;
    }
    int getposX()const{
        return posX;
    }
    void setposY(int y){
        Object::posY=y;
    }
    int getposY()const{
        return posY;
    }
    std::string getName()const{
        return name;
    }
protected:
int movements;
int posX;
int posY;
std::string name;


};

#endif //MAIN_OBJECT_H
