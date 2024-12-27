#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
class MenuComponement
{
public:
    virtual void add(MenuComponement* menuComponement){}
    virtual void remove(MenuComponement* menuComponement){}
    virtual MenuComponement* getChild(int i){}
    virtual std::string getName(){}
    virtual int getAge(){}
    virtual void print(){}
};


class Menu:public MenuComponement
{
    std::vector<MenuComponement*> Menus;
    std::string name;
    std::string description;
public:
    Menu(std::string Name,std::string Description)
    {
        this->name = Name;
        this->description = Description;
    }
    void add(MenuComponement* menuComponement) override
    {
        Menus.push_back(menuComponement);
    }
    void remove(MenuComponement* menuComponement) override
    {
        Menus.erase(std::remove(Menus.begin(), Menus.end(), menuComponement),Menus.end());
    }
    MenuComponement* getChild(int i) override
    {
        return Menus[i];
    }
    void print() override
    {
        std::cout<<this->name<<std::endl<< this->description<<std::endl;
        for (auto M : Menus)
        {
            M->print();
        }
    }
};


class MenuItem:public MenuComponement
{
    std::string name;
    int age;

public:
    MenuItem(std::string str,int age)
    {
        this->name = str;
        this->age = age;
    }

    void print() override
    {
        std::cout<<this->name<<std::endl;
        std::cout<< this->age<<std::endl;

    }

    std::string getName() override
    {
        return this->name;
    }

    int getAge() override
    {
        return this->age;
    }

};


class Waitress
{
    MenuComponement* AllMenus;
public:
    Waitress(MenuComponement* allMenus)
    {
        this->AllMenus = allMenus;
    }
    void printAll()
    {
        this->AllMenus->print();
    }
};


int main()
{

    MenuComponement* Menu1 = new Menu("Menu1","´óÈø´ïÈø´ï");
    MenuComponement* Menu2 = new Menu("Menu2","ewqewq");
    MenuComponement* Menu1Item1 = new MenuItem("M1I1",15);
    MenuComponement* Menu1Item2 = new MenuItem("M1I2",12);
    Menu1->add(Menu1Item1);
    Menu1->add(Menu1Item2);
    MenuComponement* Menu2Item1 = new MenuItem("M2I1",15);
    MenuComponement* Menu2Item2 = new MenuItem("M2I2",12);
    Menu2->add(Menu2Item1);
    Menu2->add(Menu2Item2);
    MenuComponement* AllMenu = new Menu("ALL MENU iS ME!","hahahha!");
    AllMenu->add(Menu1);
    AllMenu->add(Menu2);
    auto Waitress(AllMenu);
    Waitress->print();
}
