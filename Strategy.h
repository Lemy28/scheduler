
#ifndef SCHEDULER_STRATEGY_H
#define SCHEDULER_STRATEGY_H

/*
#include <json/Json.h>
using namespace json;
*/

#include <task/Task.h>
#include <vector>
#include <algorithm>

using namespace std;
using namespace task;


class Strategy {
public:

    static Strategy* get_instance();

    //根据到达时间排序
    virtual void sort(std::vector<Task> &tasks);
    //选出已经到达的任务
    virtual int select(std::vector<Task> &todo);
    string strategyname{"FCFS"};


protected:
    Strategy()=default;

};

//静态最高优先级优先SHPF
class SHPF:public Strategy {

public:
    void sort(std::vector<Task> &tasks) override;
    SHPF(){
        strategyname = "SHPF";
    }

};


//先来先服务算法FCFS
class FCFS:public Strategy {
public:
    FCFS()=default;
};


//时间片轮转算法RR 有问题
class RR:public Strategy{
    static unsigned int index;
public:
    int select(std::vector<Task> &tasks) override;
    RR(){
        strategyname = "RR";
    }
};

//最短作业优先SJF
class SJF :public Strategy{
public:
    void sort(std::vector<Task> &tasks) override;
    SJF(){
        strategyname = "SJF";
    }

};

//高响应比算法HRRN
class HRRN:public Strategy{
public:
    void sort(std::vector<Task> &tasks) override;
    HRRN(){
        strategyname = "HRRN";
    }
    static double get_response_rate(const Task &task);
};

#endif //SCHEDULER_STRATEGY_H
