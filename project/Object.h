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
    void setMovements(float variation){
        Object::movements=variation;
    }
    float getMovements()const{
        return movements;
    }
    void setposX(float x){
        Object::posX=x;
    }
    float getposX()const{
        return posX;
    }
    void setposY(float y){
        Object::posY=y;
    }
    float getposY()const{
        return posY;
    }
    std::string getName()const{
        return name;
    }
    void setTileNumber(int tileNumber) {
        Object::tileNumber = tileNumber;
    }
    const std::string &getTextureFile() const{
        return textureFile;
    }
    void setTextureFile(const std::string &textureFile) {
        Object::textureFile = textureFile;
    }

protected:

    float movements=0;
    float posX=0;
    float posY=0;
    std::string name;
    float tileNumber=0;
    std::string textureFile;
};

#endif //MAIN_OBJECT_H
