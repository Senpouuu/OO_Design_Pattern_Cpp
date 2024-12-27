#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

std::mt19937 rng(std::random_device{}());
std::uniform_int_distribution<int> dist(1, 100);

class Observer
{
public:
	const char* name = "NaN";
	virtual void update() = 0;
	virtual void display() = 0;
    Observer(const char * name)
    {
        this->name = name;
    }
};

class Subject
{
public:
	virtual void registerObserver(Observer* o) = 0;
	virtual void removeObserver(Observer* o) = 0;
	virtual void notifyObserver() = 0;
};


class WeatherData:public Subject
{

private:
	std::vector<Observer*> ObsVector;
	static inline int temp = 0, humi = 0, press = 0;

public:
	void registerObserver(Observer* o) override
	{
		ObsVector.push_back(o);
        std::cout << "Obsver" << o->name << "registered!\r\n";
	}


	void removeObserver(Observer* o) override
	{
		std::vector<Observer*>::iterator it; // 定义一个迭代器
		it = std::find(ObsVector.begin(), ObsVector.end(), o); // 在向量中查找 x
		if (it != ObsVector.end()) // 如果找到了 x
		{
			ObsVector.erase(it); // 删除 x
			std::cout << "Obsver" << o->name << "Deleted!";
		}
		else
		{
			std::cout << "Obsver is not Subcirbed!";
		}

	}

	void notifyObserver() override
	{
        if (!ObsVector.empty())
		    for (auto x : ObsVector)
		    	x->update();
        else
            std::cout<<"暂无订阅者";

	}
	static int getTemp()
	{

        return temp;
	}

    static int getHumi()
	{
        return humi;
	}

	static int getPress()
	{
        return press;
	}

	void DataChanged()
    {
        //set Data
        temp = dist(rng);
        humi = dist(rng);
        press = dist(rng);
        this->notifyObserver();
	}

};


class TempDisplay:public Observer
{
public:
    int temp = 0;
    TempDisplay(const char* name)
    : Observer(name)
    {
    }
    void update() override
	{
        this->temp = WeatherData::getTemp() ;
        this->display();
	}

	void display() override
	{
        std::cout<<"现在的温度是："<< this->temp<<std::endl;
	}

};

class HumiDisplay:public Observer
{
public:
    int humi = 0;
    HumiDisplay(const char* name)
    : Observer(name)
    {
    }
    void update() override
	{
        this->humi = WeatherData::getHumi();
        this->display();
	}

	void display() override
	{
        std::cout<<"现在的湿度是："<< this->humi<<std::endl;
	}

};

class DisplayAvg:public Observer
{
public:
    float avg = 0;

    DisplayAvg(const char * name)
    : Observer(name)
    {
    }

    void update() override
	{
        this->avg = (WeatherData::getHumi() + WeatherData::getTemp() + WeatherData::getPress())/3;
        this->display();
	}

	void display() override
	{
        std::cout<<"现在的平均是："<< this->avg<<std::endl;

	}


};



int main()
{
    auto Weather = new WeatherData();
    auto Display = new TempDisplay("TempDisplay1");
    auto Display2 = new HumiDisplay("HumiDisplay2");
    auto Display_avg = new DisplayAvg("DisplayAvg1");
    Weather->registerObserver(Display);
    Weather->registerObserver(Display_avg);
    Weather->registerObserver(Display2);
    Weather->DataChanged();
    while(1)
    {
        std::cin.get();
        Weather->DataChanged();
    }
}