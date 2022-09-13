//
// Created by tommy on 28/07/2022.
//
#include "Subject.h"

void Subject::attach(Observer *newObserver) {
    _observers.push_back(newObserver);
}

void Subject::detach(Observer *newObserver) {
    int count = _observers.size();
    int i;

    for (i = 0; i < count; i++) {
        if (_observers[i] == newObserver)
            break;
    }

    if (i < count)
        _observers.erase(_observers.begin() + i);
}

void Subject::notify() {
    int count = _observers.size();

    for (int i = 0; i < count; i++)
        (_observers[i])->update(this);
}