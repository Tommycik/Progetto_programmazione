//
// Created by tommy on 17/06/2022.
//

#include "Dice.h"

#include <ctime> // for time
#include <cstdlib> // for rand and srand

int Dice::numRolls = 0;

Dice::Dice(int f) : faces(f) {
    srand(time(0));
}

int Dice::roll(int r) {
    int result = 0;

    if ((numRolls % maxRolls) == 0)
        srand(time(0));

    for (int i = 0; i < r; i++)
        result += rand() % faces + 1;
    numRolls++;
    return result;
}
