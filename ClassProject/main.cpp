#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>


class Course {
public:
    // ���캯�������ڳ�ʼ���γ̶���
    Course(int id, std::string name, int credits, bool isCore)
        : courseID(id), courseName(name), courseCredits(credits), isCoreCourse(isCore) {}

    // ��Ա���������ڻ�ȡ�γ̵�ID
    int getID() const
    {
        return courseID;
    }

    // ��Ա���������ڻ�ȡ�γ̵�����
    std::string getName() const
    {
        return courseName;
    }

    // ��Ա���������ڻ�ȡ�γ̵�ѧ��
    int getCredits() const
    {
        return courseCredits;
    }

    // ��Ա���������ڼ���Ƿ�Ϊרҵ������
    bool isCore() const
    {
        return isCoreCourse;
    }

    // ��Ա���������ڴ�ӡ�γ̵���Ϣ
    void printCourseInfo() const
    {
        std::cout << "Course ID: " << courseID << "\t";
        std::cout << "Course Name: " << courseName << "\t";
        std::cout << "Credits: " << courseCredits << "\t";
        std::cout << (isCoreCourse ? "Core Course" : "Elective Course") << std::endl;

    }

private:
    int courseID;           // �γ�ID
    std::string courseName;  // �γ�����
    int courseCredits;       // ѧ��
    bool isCoreCourse;       // �Ƿ�Ϊרҵ������
};


class Observer
{
    virtual void update(std::string data){};
    virtual void update(std::vector<Course> Plan){};

public:
    std::string ID;
};

class Factory
{
public:
    virtual Observer* createItem(std::string info) = 0;
};

class Subject
{
    virtual void registerObserver(std::string info) = 0;
    virtual void removeObserver(std::string ID) = 0;
protected:
    std::vector<Observer*> ObsVector;
    Observer* findObserverByID(std::string targetID)
    {
        auto it = std::find_if(ObsVector.begin(), ObsVector.end(),
            [targetID](Observer* obs) {
                return obs->ID == targetID;
            });

        if (it != ObsVector.end()) {
            return *it; // �����ҵ��� Observer ָ��
        }

        return nullptr; // ���δ�ҵ�ƥ��� ID���򷵻ؿ�ָ��
    }

};


// ���ɴ�ʱ������ַ���ID
std::string generateTimestampStringID()
{
    std::time_t currentTime = std::time(nullptr);
    struct std::tm* timeInfo = std::localtime(&currentTime);

    // ����һ���ַ���ID������������ʱ����
    std::ostringstream idStream;
    idStream << (timeInfo->tm_year + 1900)
             << (timeInfo->tm_mon + 1)
             << timeInfo->tm_mday
             << timeInfo->tm_hour
             << timeInfo->tm_min
             << timeInfo->tm_sec;

    return idStream.str();
}



class Apply
{
public:
    std::string Apply_info;
    int Apply_state;

    //0 δ��� 1���ͨ�� 2���δͨ��
    Apply(std::string info)
    {
        Apply_info = info;
        Apply_state = 0;
    }

};



class Apply_Observer:public Observer
{
public:
    Apply_Observer(std::string info)
    {
        ID = generateTimestampStringID();
        this->apply = new Apply(info);
    }
    void update(std::string ID) override
    {
        int state = stoi(ID);
        this->apply->Apply_state = state;
    }
    std::string getApplyInfo()
    {
        return this->apply->Apply_info;
    }

private:
    Apply* apply;
};


class Apply_Factory:public Factory
{
public:
    Observer * createItem(std::string info) override
    {
        Observer* obs = new Apply_Observer(info);
        return obs;
    }
};



class Apply_Subject:public Subject
{
private:
    static inline int Apply_state;
    Factory* factory = new Apply_Factory();


public:
    void registerObserver(std::string info) override
    {
        auto obs = factory->createItem(info);
        ObsVector.push_back(obs);
        auto Cobs = dynamic_cast<Apply_Observer*>(obs);
        std::cout<<obs->ID << " "<< Cobs->getApplyInfo() <<" Registered!\r\n";
    }

    void removeObserver(std::string ID) override
    {
        auto obs = findObserverByID(ID);
        auto it = std::remove(ObsVector.begin(), ObsVector.end(), obs);
        if (it != ObsVector.end())
        {
            ObsVector.erase(it); // ɾ��ƥ��Ĺ۲���
            std::cout << "Observer " << ID << " Deleted!" << std::endl;
        }
        else
            std::cout << "Observer " << ID << " not found in the vector!" << std::endl;
    }

    void examine_Apply(std::string ID,int state)
    {
        auto obs = findObserverByID(ID);
        if (state != 1 && state != 2)
            std::cout<< "1���ͨ�� 2���δͨ��\r\n" ;
        else
        {
            auto Cobs = dynamic_cast<Apply_Observer*>(obs);
            Cobs->update(std::to_string(state));
        }
    }

};



class Courses
{
public:

    static std::vector<Course> getCourses() {
        std::vector<Course> courses;
        courses.emplace_back(1, "Math", 3, true);
        courses.emplace_back(2, "History", 4, false);
        courses.emplace_back(3, "Computer Science", 4, true);
        courses.emplace_back(4, "Biology", 3, false);
        courses.emplace_back(5, "Physics", 5, true);
        courses.emplace_back(6, "Chemistry", 4, false);
        return courses;
    }

    static inline std::vector<Course> courses = getCourses();


    static Course findCourseByID(int id)
    {
        for (const Course& course : courses) {
            if (course.getID() == id) {
                return course;
            }
        }
        // ���δ�ҵ�ƥ��Ŀγ̣������׳��쳣�򷵻�һ��Ĭ�ϵ�Course����
        std::cout<<"Course Not Found";
        return Course(-1, "Not Found", 0, false);
    }

    static Course findCourseByName(const std::string& name)
    {
        for (const Course& course : courses) {
            if (course.getName() == name) {
                return course;
            }
        }
        // ���δ�ҵ�ƥ��Ŀγ̣������׳��쳣�򷵻�һ��Ĭ�ϵ�Course����
        std::cout<<name<<"Not Found";
        return Course(-1, "Not Found", 0, false);
    }

};




class RaisePlan_Observer:public Observer
{
public:
    RaisePlan_Observer(std::string id)
    {
        ID = id;
    }
private:
    std::vector<Course> RaisePlan;
    void AddRisePlan(std::string name)
    {
        //��������ܸ�ѡ
       RaisePlan.push_back(Courses::findCourseByName(name));
    }

     void DeleteRisePlan(const std::string& name)
     {
        // ����Ҫɾ���Ŀγ̶���
        auto it = std::remove_if(RaisePlan.begin(), RaisePlan.end(),
            [name](const Course& course) { return course.getName() == name; });

        if (it != RaisePlan.end())
            RaisePlan.erase(it, RaisePlan.end()); // ��������ɾ��ƥ��Ŀγ̶���
        else
            std::cout<<name<<" not Found!";
    }

public:
    void update(std::vector<Course> plan) override
    {


    }

     std::vector<Course> getRaisePlan()
     {
         return RaisePlan;
     }

};

class RaisePlanFactory:public Factory
{
public:
    Observer * createItem(std::string info) override
    {
        auto Rai = RaisePlan_Observer(info);
    }
};


class RaisePlan_Subject:public Subject
{
private:
   RaisePlanFactory* Factory = new RaisePlanFactory;

public:
    void registerObserver(std::string id) override
    {
        auto obs = Factory->createItem(id);
        ObsVector.push_back(obs);
    }

    void removeObserver(std::string ID) override
    {
        auto obs = findObserverByID(ID);
        auto it = std::remove(ObsVector.begin(), ObsVector.end(), obs);
        if (it != ObsVector.end())
        {
            ObsVector.erase(it); // ɾ��ƥ��Ĺ۲���
            std::cout << "Observer " << ID << " Deleted!" << std::endl;
        }
        else
            std::cout << "Observer " << ID << " not found in the vector!" << std::endl;
    }

    void EditRaisePlan(std::string ID)
    {
        auto obs = findObserverByID(ID);
        auto Cobs = dynamic_cast<RaisePlan_Observer*>(obs);
        auto Plan = Cobs->getRaisePlan();
        //do Edit
        Cobs->update(Plan);
    }

    void ArrangeRaisePlan(std::string ID)
    {
        auto obs = findObserverByID(ID);
        auto Cobs = dynamic_cast<RaisePlan_Observer*>(obs);
        auto Plan = Cobs->getRaisePlan();
        //do Arrange
        Cobs->update(Plan);
    }
};



int main()
{
    auto course = Courses::courses;
    auto ss = new Apply_Subject();
    auto id = generateTimestampStringID();
    ss->registerObserver("�����Ӹģ�");
    ss->examine_Apply(id,1);
    std::cin.get();
    return 0;
}
