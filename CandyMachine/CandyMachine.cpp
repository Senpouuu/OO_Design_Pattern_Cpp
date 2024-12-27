#include "CandyMachine.h"


CandyMachine::CandyMachine(int numCandys) : count(numCandys) {
    soldOutState = new SoldOutState(this);
    noQuarterState = new NoQuarterState(this);
    hasQuarterState = new HasQuarterState(this);
    soldState = new SoldState(this);
    winnerState = new WinnerState(this);

    state = (count > 0) ? noQuarterState : soldOutState; // 根据糖果数量设置初始状态
}

void CandyMachine::setState(State* s) {
    state = s;
}


State* CandyMachine::getSoldOutState() {
    return soldOutState;
}

State* CandyMachine::getNoQuarterState() {
    return noQuarterState;
}

State* CandyMachine::getHasQuarterState() {
    return hasQuarterState;
}

State* CandyMachine::getSoldState() {
    return soldState;
}

State *CandyMachine::getWinnerState() {
    return winnerState;
}
