
#ifndef SCHEDULER_PCB_H
#define SCHEDULER_PCB_H

#include <iostream>

#define READY 0
#define FINISH 1
#define RUNNING 2

namespace task{

struct PCB{   //进程控制块

public:

    double servicetime{0};              //运行时间
    double  waittime{0};                  //等待时间
    static unsigned int processcounter;     //进程计数器
    unsigned int pid{0};                       //进程号
    int status{0};                             //进程状态 0-就绪 1-完成 2-运行

    PCB(){
        pid = ++processcounter;

    }

    double get_servicetime()const{
        return servicetime;
    }

    void set_servicetime(double setval){
        servicetime = setval;
    }


    double get_waittime ()  const{
        return waittime;
    }


    static void reset_counter(){
        processcounter = 0;
    }
    ~PCB(){
    }
};

}//task namespace

#endif //SCHEDULER_PCB_H
