
#ifndef SCHEDULER_TASK_H
#define SCHEDULER_TASK_H

#include "PCB.h"
#include <string>

namespace task{

class Task {
public:
    int static_prio;               //静态优先级
    unsigned int arrivetime;       //到达时刻
    unsigned int requesttime;      //要求运行时间
    PCB pcb;                       //进程控制块

    //构造函数
    Task(int prio=0,int arrtime=0,int requesttime=0):static_prio(prio),arrivetime(arrtime),requesttime(requesttime),pcb(){}
    //计算任务还需要的时间
    double get_need()const;
    //判断任务是否到达
    bool arrived(double curtime);

    //周转时间
    double get_turnaround_time(){

        return pcb.get_waittime() +requesttime;
    }
    //带权周转时间
    double get_weighted_turnaround_time(){
        return get_turnaround_time()/requesttime;
    }


    //响应比
    double get_response_ratio(){
        return get_weighted_turnaround_time()/pcb.get_waittime();
    }

};

}

#endif //SCHEDULER_TASK_H
