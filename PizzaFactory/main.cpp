#include <iostream>
#include <string>
class Pizza {
public:
    std::string name = "Just Pizza";

    virtual void cut()
    {
        std::cout << "Cut!\r\n";
    }

    virtual void bake()
    {
        std::cout<<"bake\r\n";
    }
    virtual void prepare()
    {
        std::cout<<"prepare!\r\n";
    }

};

class PizzaMaterialFactory
{
    virtual std::string Milk() = 0;
    virtual std::string Salt() = 0;
};

class WesternMaterialFactory:public PizzaMaterialFactory
{
public:
    std::string Milk() override
    {
        return "Milk ";
    }

    std::string Salt() override
    {
        return "a little Salt ";
    }
};

class NormalMaterialFactory:public PizzaMaterialFactory
{
public:
    std::string Milk() override
    {
        return "a little Milk ";
    }

    std::string Salt() override
    {
        return "Salt ";
    }

};


class CheesePizza:public Pizza
{
public:
    std::string milk;
    CheesePizza(std::string PizzaName)
    :Pizza()
    {
        name = PizzaName;
    }
    void prepare() override
    {
        auto Mfactory = new WesternMaterialFactory();
        std::cout<<"Adding Some "<< Mfactory->Salt() << Mfactory->Milk() << std::endl;
    }

};

class SugarPizza:public Pizza
{
public:
    std::string milk;
    SugarPizza(std::string PizzaName)
    :Pizza()
    {
        name = PizzaName;
    }

};

class ChinesePizza:public Pizza
{
public:
    std::string salt;
    ChinesePizza(std::string PizzaName)
    :Pizza()
    {
        name = PizzaName;
    }

};

class PizzaStore
{
protected:
    Pizza* pizza = NULL;
public:
    virtual Pizza* makepizza(std::string PizzaName) = 0;

    virtual void sellpizza(std::string PizzaName)
    {
        pizza = makepizza(PizzaName);
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        std::cout<<"Your "<<pizza->name<<"Pizza is ok Sir!\r\n";
    }
};


class ChinesePizzaStore:public PizzaStore
{
    Pizza* makepizza(std::string PizzaName) override
    {
        if(PizzaName == "Chinese")
            pizza = new CheesePizza(PizzaName);
        return pizza;
    }
};






int main() {
   auto Store = new ChinesePizzaStore;
   Store->sellpizza("Chinese");
}
