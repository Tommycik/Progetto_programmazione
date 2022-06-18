//
// Created by tommy on 17/06/2022.
//

#include "Dice.h"

#include <ctime> // for time
#include <cstdlib> // for rand and srand

int Dice::numRolls = 0;

Dice::Dice(int f) : faces(f) {
    // read: https://stackoverflow.com/questions/7343833/srand-why-call-it-only-once
    srand(time(0));
}


int Dice::roll(int r) {
    int result = 0;

    // XXX it goes against the best practice. Set a very high number for max num rolls
    // read: https://stackoverflow.com/questions/1452934/what-is-the-meaning-of-xxx-in-code-comments
    if ((numRolls % maxRolls) == 0)
        srand(time(0));

    for (int i = 0; i < r; i++)
        result += rand() % faces + 1;
    numRolls++;
    return result;
}
