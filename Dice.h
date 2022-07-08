//
// Created by tommy on 17/06/2022.
//

#ifndef MAIN_DICE_H
#define MAIN_DICE_H


class Dice {
public:
    Dice();
    explicit Dice(int f = 6);

    int roll(int r);

private:
    int faces;
    static int numRolls;
    const int maxRolls = 1000; // max number of rolls, when numRolls > maxR
};


#endif //MAIN_DICE_H
