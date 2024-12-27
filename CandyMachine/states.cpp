#include "states.h"
#include "CandyMachine.h"
#include <iostream>

NoQuarterState::NoQuarterState(CandyMachine* cm) : candyMachine(cm) {}

void NoQuarterState::insertQuarter() {
    if (candyMachine->winnerCount == 10)
        candyMachine->setState(candyMachine->getWinnerState());


    else
    {
        candyMachine->winnerCount++;
        candyMachine->setState(candyMachine->getHasQuarterState());
    }
    std::cout << "Coin inserted\r\n";
}

void NoQuarterState::ejectQuarter() {
    std::cout << "No coin\r\n";
}

void NoQuarterState::turnCrank() {
    std::cout << "No coin\r\n";
}

void NoQuarterState::dispense() {
    std::cout << "No coin\r\n";
}

HasQuarterState::HasQuarterState(CandyMachine* cm) : candyMachine(cm) {}

void HasQuarterState::insertQuarter() {
    std::cout << "Cannot insert another coin\r\n";
}

void HasQuarterState::ejectQuarter() {
    candyMachine->setState(candyMachine->getNoQuarterState());
    std::cout << "Coin returned\r\n";
}

void HasQuarterState::turnCrank() {
    candyMachine->setState(candyMachine->getSoldState());
    std::cout << "Dispensing...\r\n";
}

void HasQuarterState::dispense() {
    candyMachine->count--;
    std::cout << "Please take your candy\r\n";
    if (candyMachine->count == 0) {
        candyMachine->setState(candyMachine->getSoldOutState());
    }
}

SoldState::SoldState(CandyMachine* cm) : candyMachine(cm) {}

void SoldState::insertQuarter() {
    std::cout << "Please wait...\r\n";
}

void SoldState::ejectQuarter() {
    std::cout << "Cannot return coin during dispensing...\r\n";
}

void SoldState::turnCrank() {
    std::cout << "Cannot turn crank during dispensing...\r\n";
}

void SoldState::dispense() {
    candyMachine->setState(candyMachine->getNoQuarterState());
    std::cout << "Please take your candy...\r\n";
}

SoldOutState::SoldOutState(CandyMachine* cm) : candyMachine(cm) {}

void SoldOutState::insertQuarter() {
    std::cout << "Sold out...\r\n";
}

void SoldOutState::ejectQuarter() {
    std::cout << "Sold out...\r\n";
}

void SoldOutState::turnCrank() {
    std::cout << "Sold out...\r\n";
}

void SoldOutState::dispense() {
    std::cout << "Sold out...\r\n";
}

WinnerState::WinnerState(CandyMachine *cm) : candyMachine(cm) {}

void WinnerState::insertQuarter()
{
    std::cout << "Cannot insert another coin\r\n";
}

void WinnerState::ejectQuarter() {
    candyMachine->setState(candyMachine->getNoQuarterState());
    std::cout << "Coin returned\r\n";
}

void WinnerState::turnCrank() {
    std::cout << "Trunning...\r\n";
}

void WinnerState::dispense() {
    candyMachine->winnerCount = 0;
    candyMachine->setState(candyMachine->getNoQuarterState());
    std::cout << "You get two Candy!\r\n";
}
