#include <iostream>
#include "CandyMachine.h"


int main() {
    auto cm = new CandyMachine(5);
    cm->state->insertQuarter();
    cm->state->turnCrank();
    cm->state->dispense();

    for (int num = 1;num<12;num++)
    {
        cm->state->insertQuarter();
        cm->state->turnCrank();
        cm->state->dispense();
    }


    return 0;
}
