#ifndef CANDYMACHINE_CANDYMACHINE_H
#define CANDYMACHINE_CANDYMACHINE_H

#include "states.h"

class CandyMachine {
public:
    CandyMachine(int numCandys);

    void setState(State* s);
    State* getSoldOutState();
    State* getNoQuarterState();
    State* getHasQuarterState();
    State* getSoldState();
    State* getWinnerState();

    int count;
    int winnerCount = 0;

    State* soldOutState{};
    State* noQuarterState{};
    State* hasQuarterState{};
    State* soldState{};
    State* winnerState{};

    State* state{};


};

#endif // CANDYMACHINE_CANDYMACHINE_H
