//
// Created by tommy on 16/06/2022.
//

#ifndef MAIN_BOSS_H
#define MAIN_BOSS_H

#include "Skills.h"

class Boss : public Entity {
public:

    void run(float x, float y) override;

    int getStatIncrease() const;

    void setStatIncrease(int statIncrease);

    virtual std::unique_ptr<Skills> skillUse() = 0;

protected:

    int statIncrease = 1;
    int skillType = 0;
    int dungeonNumber = 0;
};

#endif //MAIN_BOSS_H
