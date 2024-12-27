#ifndef CANDYMACHINE_STATES_H
#define CANDYMACHINE_STATES_H

class CandyMachine; // 前向声明

class State {
public:
    virtual void ejectQuarter() = 0;
    virtual void turnCrank() = 0;
    virtual void dispense() = 0;
    virtual void insertQuarter() = 0;
    virtual ~State() = default;  // 虚析构函数
};

class NoQuarterState : public State {
public:
    NoQuarterState(CandyMachine* cm);
    void insertQuarter() override;
    void ejectQuarter() override;
    void turnCrank() override;
    void dispense() override;

    CandyMachine* candyMachine;
};

class HasQuarterState : public State {
public:
    HasQuarterState(CandyMachine* cm);
    void insertQuarter() override;
    void ejectQuarter() override;
    void turnCrank() override;
    void dispense() override;

    CandyMachine* candyMachine;
};

class SoldState : public State {
public:
    SoldState(CandyMachine* cm);
    void insertQuarter() override;
    void ejectQuarter() override;
    void turnCrank() override;
    void dispense() override;

    CandyMachine* candyMachine;
};

class SoldOutState : public State {
public:
    SoldOutState(CandyMachine* cm);
    void insertQuarter() override;
    void ejectQuarter() override;
    void turnCrank() override;
    void dispense() override;

    CandyMachine* candyMachine;
};


class WinnerState: public State {
public:
    WinnerState(CandyMachine* cm);
    void insertQuarter() override;
    void ejectQuarter() override;
    void turnCrank() override;
    void dispense() override;

    CandyMachine* candyMachine;
};

#endif // CANDYMACHINE_STATES_H