#include <iostream>
#include <vector>

class Iterator
{
public:
    virtual bool hasNext() = 0;
    virtual int next() = 0;
};

class Menu1Iterator:public Iterator
{
    int* Array;
    int pos = 0;
public:
    Menu1Iterator(int* array)
    {
        this->Array = array;
    }
    int next() override
    {
        pos = pos + 1;
        return Array[pos];
    }

    bool hasNext()
    {
        int temp = pos;
        if(this->Array[temp++]!= '\0' || pos >= 10)
            return true;
        else
            return false;
    }
};

class Menu2Iterator:public Iterator
{
    std::vector<int> Array;
    int pos = 0;
public:
    Menu2Iterator(std::vector<int> array)
    {
        this->Array = array;
    }
    int next() override
    {
        pos = pos + 1;
        return Array[pos];
    }
    bool hasNext()
    {
        int temp = pos;
        if(temp < Array.size() && Array[temp] != 0)
            return true;
        else
            return false;
    }

};



class Menu1
{
public:
    int array[10];
    int len = 10;
    void addItem()
    {
        array[0] = 1;
        array[1] = 2;
        array[2] = 3;
    }
    int* getArray()
    {
        return array;
    }
    Iterator* createIterator()
    {
        Iterator* Iter = new Menu1Iterator(array);
        return Iter;
    }

};


class Menu2
{
public:
    std::vector<int> array;
    void addItem()
    {
        array.push_back(1);
        array.push_back(2);
        array.push_back(3);
    }
    std::vector<int> getArray()
    {
        return array;
    }
    Iterator* createIterator()
    {
        Iterator* Iter = new Menu2Iterator(this->array);
        return Iter;
    }

};






int main() {
    auto m1 = new Menu1();
    auto m2 = new Menu2();
    m1->addItem();
    m2->addItem();
    auto Iter1 = m1->createIterator();
    auto Iter2 = m2->createIterator();
    int i = 0;
    std::cout<<"asdsadasd";
    while(Iter1->hasNext())
    {
        i ++;
        std::cout<<"第"<<i<<"个元素："<<Iter1->next()<<std::endl;
    }
    int j = 0;
    while(Iter2->hasNext())
    {
        j ++;
        std::cout<<"第"<<j<<"个元素："<<Iter2->next()<<std::endl;
    }

}
