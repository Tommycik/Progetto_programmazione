//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_LITTLELIGHT_H
#define MAIN_LITTLELIGHT_H
#include <iostream>
#include <vector>
#include "Entity.h"

class Littlelight:public  Entity {

public:

    virtual void move(float x, float y) override;

private:
    int status;
    bool appear;
    std::vector<std::string> dialogue; //è un array ma per ora è un segnaposto
};


#endif //MAIN_LITTLELIGHT_H
