#include <iostream>


class FlyBehavior
{
public:
    virtual void fly() = 0;
};

class QuackBehavior
{
public:
    virtual void quack() = 0;
};


class FlyWithWings : public FlyBehavior
{
    void fly() override
    {
        std::cout << "I am Flying !\r\n";
    }
};



class FlyNoWay :public FlyBehavior
{
    void fly() override
    {
        std::cout << "I cannot Fly!\r\n";
    }
};

class FlyRocket :public FlyBehavior
{
    void fly() override
    {
        std::cout << "Rocket Fly!!\r\n";
    }
};


class Quack :public QuackBehavior
{
    void quack() override
    {
        std::cout << "ßÉßÉ\r\n";
    }
};


class Squeak :public QuackBehavior
{
    void quack() override
    {
        std::cout << "¸Â¸Â\r\n";
    }
};


class MuteQuack :public QuackBehavior
{
    void quack() override
    {
        std::cout << "Mute£¡\r\n";
    }
};


class TechQuack :public QuackBehavior
{
    void quack() override
    {
        std::cout << "ßÇßÇßÇßÇßÇßÇÀ©À©À©ßÇßÇßÇßÇßÇßÇÀ©À©À©£¡\r\n";
    }
};


class Duck
{
public:
       FlyBehavior* flyBehavior;
       QuackBehavior* quackBehavior;

       Duck(FlyBehavior* flyBehavior, QuackBehavior* quackBehavior)
       {
           this->flyBehavior = flyBehavior;
           this->quackBehavior = quackBehavior;
       }

       void performFly()
       {
           flyBehavior->fly();
       }

       void performQuack()
       {
           quackBehavior->quack();
       }

       void setBehavior(FlyBehavior* flyBehavior, QuackBehavior* quackBehavior)
       {
           this->flyBehavior = flyBehavior;
           this->quackBehavior = quackBehavior;
       }

       void swim()
       {
           std::cout << "We Can Swim!\r\n";
       }
};


class MallardDuck : public Duck
{
public:
    MallardDuck() :
        Duck(new FlyWithWings(), new Quack())
    {

        std::cout << "MallDuck ÒÑÉú³É£¡\n";
    }

};


class TechDuck : public Duck
{
public:
    TechDuck() :
        Duck(new FlyRocket(), new TechQuack())
    {
        std::cout << "RockDuck£¡\r\n";
    }
};


int main()
{
    TechDuck* A = new TechDuck();
    A->performFly();
    A->performQuack();
    std::cin.get();
    A->setBehavior(new FlyWithWings, new MuteQuack);
    A->performFly();
    A->performQuack();

}




