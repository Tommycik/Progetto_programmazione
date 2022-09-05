//
// Created by tommy on 13/08/2022.
//

#ifndef MAIN_SKILLMANAGER_H
#define MAIN_SKILLMANAGER_H
#include"Observer.h"
#include "World.h"
#include "Loader.h"

class SkillManager: public Observer {

public:

    SkillManager(World &game,TileMap &skills);
    ~SkillManager();

    virtual void update(Subject *theChangedSubject) override;
    void draw();

private:

    World *_subject;
    TileMap *skills;
    int skillNumber=0;
};


#endif //MAIN_SKILLMANAGER_H
