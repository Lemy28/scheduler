
#ifndef SCHEDULER_SCHEDULER_H
#define SCHEDULER_SCHEDULER_H
#include "Strategy.h"
#include "Timer.h"
#include <vector>

class Scheduler {

public:

    Scheduler(Strategy* strategy,std::vector<Task>  &tasks,double slide);
    ~Scheduler(){
        delete sche_strategy;
    }
    double run_task(Task &task);
    void start();
    void show();
    void report();

private:
    std::vector<Task> approach; //快要到达的任务
    std::vector<Task> todo; //已经到达的任务
    std::vector<Task> finished{};//完成的任务

    Timer timer;
    Strategy* sche_strategy;
    void schedule();
    //检查是否有已经到达的任务
    void check(double now);
    };





#endif //SCHEDULER_SCHEDULER_H
