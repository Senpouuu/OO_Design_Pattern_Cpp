#include <iostream>
#include <string>
class Beverage
{
public:
    std::string description = "NaN";

    virtual float cost() = 0;

    virtual std::string getDescription()
    {
        return description;
    }
};

class CondimentDecorator:public Beverage
{
protected:
    Beverage* beverage;
};

class Cola:public Beverage
{
public:
    Cola(): Beverage()
    {
       description = "Cola";
    }
    float cost() override
    {
        return 3;
    }
};


class Milk:public Beverage
{
public:
    Milk(): Beverage()
    {
       description = "Milk";
    }
    float cost() override
    {
        return 4;
    }

};


class Sugar:public CondimentDecorator
{
public:
    Sugar(Beverage* b)
    {
        beverage = b;
    }

    float cost() override
    {
        return 1 + beverage->cost();
    }

    std::string getDescription() override
    {
        return beverage->getDescription() + ",With Sugar";
    }

};

class Salt:public CondimentDecorator
{
public:
    float cost() override
    {
        return 1 + beverage->cost();
    }

    std::string getDescription() override
    {
        return beverage->getDescription() + ",With Salt";
    }


    Salt(Beverage* b)
    {
        beverage = b;
    }
};

class discount:public CondimentDecorator
{
public:
    float cost() override
    {
        return beverage->cost()*0.95;
    }

    std::string getDescription() override
    {
        return beverage->getDescription() + ",With 95% disCount!";
    }

    discount(Beverage* b)
    {
        beverage = b;
    }
};

int main()
{
    Beverage* milk = new Milk();
    milk = new Salt(milk);
    milk = new Salt(milk);
    milk = new Sugar(milk);
    std::cout << "Description: " << milk->getDescription() << ", Cost: " << milk->cost() << std::endl;

    Beverage* cola = new Cola();
    cola = new Salt(cola);
    cola = new Salt(cola);
    cola = new Sugar(cola);
    std::cout << "Description: " << cola->getDescription() << ", Cost: " << cola->cost() << std::endl;

    Beverage* dmilk = new Milk();
    dmilk = new Salt(dmilk);
    dmilk = new Sugar(dmilk);
    dmilk = new discount(dmilk);
    std::cout << "Description: " << dmilk->getDescription() << ", Cost: " << dmilk->cost() << std::endl;
}
