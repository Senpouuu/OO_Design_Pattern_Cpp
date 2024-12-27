#include <iostream>

class Singleton
{
private:
    static inline Singleton* ptr = nullptr;
    Singleton()
    {
        //do something

    }
public:
    static Singleton* getInstance()
    {
        if(ptr == nullptr)
            ptr = new Singleton;
        return ptr;
    }
    Singleton(const Singleton&) = delete; // 禁止拷贝构造
    Singleton& operator=(const Singleton&) = delete; // 禁止赋值运算
};



int main()
{
    auto ptr1 = Singleton::getInstance();
    auto ptr2 = Singleton::getInstance();
    auto compare = [](Singleton* a,Singleton* b)->bool { if (a==b) return true; else return false;};
    std::cout<<compare(ptr1,ptr2);


}
