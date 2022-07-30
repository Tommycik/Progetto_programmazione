//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H
#include <iostream>

class Object {

public:

    virtual ~Object() { }


    int getTileNumber() const{
        return tileNumber;
    }
    void setMovements(int variation){
        Object::movements=variation;
    }
    int getMovements()const{
        return movements;
    }
    void setposX(int x){
        Object::posX=x;
    }
    float getposX()const{
        return posX;
    }
    void setposY(int y){
        Object::posY=y;
    }
    float getposY()const{
        return posY;
    }
    std::string getName()const{
        return name;
    }

protected:

    int movements=0;
    float posX=0;
    float posY=0;
    std::string name;
    int tileNumber=0;

};

#endif //MAIN_OBJECT_H
