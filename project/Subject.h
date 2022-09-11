//
// Created by tommy on 28/07/2022.
//

#ifndef MAIN_SUBJECT_H
#define MAIN_SUBJECT_H

#include "Observer.h"
#include <vector>

class Observer;

class Subject {

public:

    Subject() {};

    virtual ~Subject() {};

    virtual void attach(Observer *newObserver);

    virtual void detach(Observer *newObserver);

    virtual void notify();

private:

    std::vector<Observer *> _observers;
};


#endif //MAIN_SUBJECT_H
