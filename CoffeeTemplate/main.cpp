#include <iostream>
#include "string"
class CoffineDrinks
{

public:
    void template_Fun()
    {
        BoilWater();
        filter();
        purlInCup();
        addCondiments();
    }


    void BoilWater()
    {
        std::cout<<"BoilWater!\r\n";
    }
    virtual void filter() = 0;

    void purlInCup()
    {
        std::cout<<"Pour In Cups !\r\n";

    }
    virtual void addCondiments() = 0;       // Hooks


};

class Coffee :public CoffineDrinks
{
    void filter() override
    {
       std::cout<<"filt Coffee!\r\n";
    }

    void addCondiments() override
    {
        char message;
        std::cout<<"some milk? Y or N?\r\n";
        scanf("%s",&message);
        if(message == 'Y')
           std::cout<<"Add some Milk!\r\n";
    }


};

class Tea:public CoffineDrinks
{
    void filter() override
    {
       std::cout<<"filt Tea!\r\n";
    }

    void addCondiments() override
    {
        char message;
        std::cout<<"some Sugar? Y or N?\r\n";
        scanf("%s",&message);
        if(message == 'Y')
           std::cout<<"Add some Sugar!\r\n";
    }

};






int main()
{
    auto tea = new Tea;
    auto coffee = new Coffee;

    tea->template_Fun();
    coffee->template_Fun();


}
