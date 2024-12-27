#include <iostream>
#include <vector>
class command
{
public:
    virtual void execute(){};
};

class light
{
public:
    void on()
    {
        std::cout<<"Light is ON!\r\n";
    }
    void off()
    {
        std::cout<<"Light is OFF!\r\n";
    }
};

class mortor
{
public:
    void on()
    {
        std::cout<<"mortor is ON!\r\n";
    }
    void off()
    {
        std::cout<<"mortor is OFF!\r\n";
    }
};


class lightOnCommand:public command
{
    light* Light;
public:
    void execute() override
    {
        Light->on();
    }

    lightOnCommand(light* l)
    {
        this->Light = l;
    }
};

class mortorOnCommand:public command
{
private:
    mortor* m;
    void execute() override
    {
        m->on();
    }
public:
    mortorOnCommand(mortor* mortor)
    {
        this->m = mortor;
    }
};

class simpleRemoteControl
{
   std::vector<command*> commands;
public:
    void setCommand(command* com)
    {
       commands.push_back(com);
    }
    void buttonWasPressed()
    {
        for (auto x:commands)
            x->execute();
    }
};




int main()
{
    auto remote = new simpleRemoteControl();
    auto Light = new light();
    auto Mortor = new mortor();
    command* LightOn = new lightOnCommand(Light);
    command* MortorOn = new mortorOnCommand(Mortor);
    remote->setCommand(LightOn);
    remote->setCommand(MortorOn);
    remote->buttonWasPressed();
}
