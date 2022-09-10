//
// Created by tommy on 08/09/2022.
//

#ifndef MAIN_SKILLUSERS_H
#define MAIN_SKILLUSERS_H
#include "Skills.h"

class SkillUsers :public Entity{

public:

    virtual std::unique_ptr<Skills> skillUse()=0;

};


#endif //MAIN_SKILLUSERS_H
