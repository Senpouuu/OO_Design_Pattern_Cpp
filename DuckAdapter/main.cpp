#include <iostream>

class Duck
{
public:
    virtual void quack() = 0;
    virtual void fly() = 0;
};


class Turkey
{
public:
    virtual void gobble() = 0;
    virtual void fly() = 0;
};


class MallardDuck:public Duck
{
public:
    void quack() override
    {
        std::cout<<"guagua!";
    }
    void fly() override
    {
        std::cout<<"I am Flying !";
    }

};

class StreetTurkey:public Turkey
{
public:
    void gobble() override
    {
        std::cout<<"gegeege!";
    }
    void fly() override
    {
        std::cout<<"I am short Flying !";
    }

};

class TurkeyAdapter:public Duck,StreetTurkey
{
public:
    void quack() override
    {
        this->gobble();
    }

    void fly() override
    {
        this->StreetTurkey::fly();
    }

};


int main()
{
    MallardDuck Duck;
    auto TDuck = new TurkeyAdapter();

    TDuck->fly();
    TDuck->quack();

}





