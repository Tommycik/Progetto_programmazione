//
// Created by tommy on 28/07/2022.
//

#ifndef MAIN_OBSERVER_H
#define MAIN_OBSERVER_H
#include "Subject.h"
class Subject;
class Observer {
public:

    Observer() {};
    virtual ~Observer() {};

    virtual void update(Subject* subjectChange) = 0;
};


#endif //MAIN_OBSERVER_H
