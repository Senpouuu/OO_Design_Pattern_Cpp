#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <time.h>
#define random(x) (rand()%x)
using namespace std;

// 定义课程类
class Course {
public:
    int courseID;           // 课程ID
    string courseName;  // 课程名称
    int courseCredits;       // 学分
    bool isCoreCourse;       // 是否为专业基础课
    int courseHours;      // 课时
    string courseTeacher;     // 老师
    int courseRoom;

    // 构造函数
    Course(int id, string name, int credits, bool core, int hours, string teacher) {
        courseID = id;
        courseName = name;
        courseCredits = credits;
        isCoreCourse = core;
        courseHours = hours;
        courseTeacher = teacher;
    }
};


class Room
{
private:
    int roomID;
    int roomNumber = 0;
    int roomTime[30][4];  // 0 日期  1 课程开始时间 2 课程结束时间  30课程ID
public:
    Room(int roomID)
    {
        this->roomID = roomID;
    }
    int getNum()
    {
        return roomNumber;
    }
    int* setClass(int week,int begin,int end,int courseID)
    {
        if(roomNumber<30)
            for (auto & i : roomTime)
                if(i != nullptr)
                    continue;
                else
                {
                    i[0] = week;
                    i[1] = begin;
                    i[2] = end;
                    i[3] = courseID;
                    roomNumber++;
                    return i;
                }
        return nullptr;
    }

};






// 定义课表矩阵
const int ROWS = 10; // 行数
const int COLS = 7; // 列数
Course* schedule[ROWS][COLS]; // 用nullptr表示空闲的格子，用Course*表示占用的格子

// 从day开始，找begin到end的空位
pair<int, int> posFinder(Course* matrix[ROWS][COLS],int day,int begin,int end)
{
    pair<int, int> result;
    // 周一到周五
    for (int i = begin; i < end; i++)
    {
        if (matrix[i][day] == nullptr)
        {
            result = std::make_pair(i, day);
            return result;
        }
    }
    return std::make_pair(-1,-1);
}


int posChecker(std::pair<int,int> idx,int courseHours,int day,int begin,int end)
{
    int row = idx.first;
    // 0123
    if (row <= 3)
    {
        int len = 4 - row;
        if(len >= courseHours)
            return 1;
        else
            return -1;
    }
    //4567
    else if (row <= 7)
    {
        int len = 7 - row;
        if(len >= courseHours)
            return 2;
        else
            return -2;
    }
    //89
    else if (row <= 9)
    {
        int len = 9 - row;
        if(len >= courseHours)
            return 3;
        else
            return -3;
    }
}

// 打印课程表
void printSchedule() {
    for (int i = 0; i < COLS - 1; ++i) {
        for (int j = 0; j < ROWS - 1; ++j) {
            if (schedule[j][i] != nullptr) {
                std::cout << "索引 (列" << i << ", " << j << "行): ";
                std::cout << "课程ID: " << schedule[j][i]->courseID << ", ";
                std::cout << "课程名称: " << schedule[j][i]->courseName << ", ";
                std::cout << "学分: " << schedule[j][i]->courseCredits << ", ";
                std::cout << "是否为专业基础课: " << (schedule[j][i]->isCoreCourse ? "是" : "否") << ", ";
                std::cout << "课时: " << schedule[j][i]->courseHours << ", ";
                std::cout << "老师: " << schedule[j][i]->courseTeacher << std::endl;
            }
        }
    }
}

std::vector<Room*> rooms;
void courseSetter(std::pair<int,int> pos,Course* course)
{
    int i = 1;
    Room* min = rooms[0];
    while(i < rooms.size() - 1)
    {
        if (min->getNum() > rooms[i]->getNum())
            min = rooms[i];
        i++;
    }
    int row = pos.first;
    int column = pos.second;
    for (int i = 0;i<course->courseHours;i++)
        schedule[row + i][column] = course;
    min->setClass(column,row,row+course->courseHours,course->courseID);


}

bool courseFiller(Course* course)
{
    int day = random(4);
    std::pair<int, int> idx = posFinder(schedule, day, 0, 3);
    int flag = posChecker(idx, course->courseHours, day, 0, 3);
    if (flag == 1)
    {
        courseSetter(idx, course);
        return true;
    }
    else
    {
        idx = posFinder(schedule, day, 4, 7);
        flag = posChecker(idx, course->courseHours, day, 4, 7);
        if (flag == 2)
        {
            courseSetter(idx, course);
            return true;
        }
        else
        {
            idx = posFinder(schedule, day, 8, 9);
            flag = posChecker(idx, course->courseHours, day, 8, 9);
            if (flag == 3)
            {
                courseSetter(idx, course);
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}


void courseArrange(std::vector<Course*> courses)
{
    auto temp = courses;
//    while(!temp.empty())
//    {
        for (auto c:temp)
        {
            auto flag = courseFiller(c);
            if (flag)
            {
                std::cout << c->courseName << flag << std::endl;
                printSchedule();
            }

        }
//    }


}


// 传入的room需要按照人数从大到小排列
void fillCourse(Course* course,std::vector<Room*> room)
{
////    for(auto r:room)
////    {
//        int flag = course->courseHours;
//        auto res = traverse(schedule,course->isCoreCourse);
//        int row = res.first;
//        int column = res.second;
//        std::cout<< row <<':' << column << std::endl;
//        for (int i = 0;i<flag;i++)
//            schedule[row + i][column] = course;
////    }
}







// 主函数
int main() {
    srand((int)time(0));
    // 创建一个课程列表
    vector<Course*> courses;
    courses.push_back(new Course(1, "数据结构", 4, true, 4, "张三"));
    courses.push_back(new Course(2, "操作系统", 4, true, 4, "李四"));
    courses.push_back(new Course(3, "计算机网络", 4, true, 2, "王五"));
    courses.push_back(new Course(4, "数据库", 4, true, 2, "赵六"));
    courses.push_back(new Course(5, "编译原理", 4, true, 4, "孙七"));
    courses.push_back(new Course(6, "软件工程", 4, true, 2, "周八"));
    courses.push_back(new Course(7, "离散数学", 4, true, 2, "吴九"));
    courses.push_back(new Course(8, "线性代数", 4, true, 2, "郑十"));
    courses.push_back(new Course(9, "英语", 2, false, 3, "陈一"));
    courses.push_back(new Course(10, "体育", 2, false, 2, "林二"));
    courses.push_back(new Course(11, "音乐", 2, false, 1, "罗三"));
    courses.push_back(new Course(12, "美术", 2, false, 1, "何四"));

    rooms.push_back(new Room(11));
    rooms.push_back(new Room(22));
    rooms.push_back(new Room(33));
    rooms.push_back(new Room(44));
    rooms.push_back(new Room(55));
    random_device rd;
    mt19937 g(rd());
    shuffle(courses.begin(), courses.end(), g);




    courseArrange(courses) ;
    printSchedule();

    return 0;
}