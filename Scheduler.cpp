#include "Scheduler.h"
#include <iomanip>
#include <unistd.h>


#include <task/Task.h>
using namespace std;
using namespace task;

Scheduler::Scheduler(Strategy* strategy, std::vector<Task> &tasks, double slide):timer(slide),approach(tasks),sche_strategy(strategy) {
    //将一开始就已经到达的任务加入到todo队列
    check(0);
}



void Scheduler::start() {

    while(!todo.empty()||!approach.empty()){
        schedule();
        //控制输出速度
        //sleep(1);
    }

    //生成运行报告
    report();

}

void Scheduler::schedule()
{


    //选出下一个被调度的进程
    int index = sche_strategy->select(todo);


    if(index>=0){

        //调度选中的进程
        todo[index].pcb.status = RUNNING;
        show();

        int cost = run_task(todo[index]);

        //添加时间
        for(auto& task:todo){
            if((task.pcb.pid!=todo[index].pcb.pid)&&task.arrived(timer.gettime()))
                //给没有被调度的进程加上等待时间
                task.pcb.waittime += cost;
        }

        //任务完成则删除
        if(todo[index].pcb.status==FINISH){
            //添加到完成队列中
            finished.push_back(todo[index]);
            todo.erase(todo.begin()+index);
        }

        timer.addtime(cost);
    }
    else{
        show();
        timer.addtime(timer.slide);
    }

    //检查是否有到达的任务
    check(timer.gettime());


}


double Scheduler::run_task(Task &task) {

    double need = task.get_need();
    double cost;

    if(need<=timer.slide)
    {
        task.pcb.servicetime = task.requesttime;
        task.pcb.status = FINISH;

        cost = need;
    }
    else{
        //耗尽一个时间片
        task.pcb.servicetime+=timer.slide;
        task.pcb.status = READY;

        cost = timer.slide;
    }


    return cost;
}



void Scheduler::report(){

    double totaltime;

    cout<<"\n策略:"<<sche_strategy->strategyname<<endl;
    cout<<"作业——————估计运行时间(分钟)——————到达时间——————等待时间——————周转时间(分钟)——————带权周转时间——————进程状态——————"<<endl;
    if(!finished.empty()){
        for(auto& item :finished){
            cout<<"job "<<item.pcb.pid<<"     ";
            cout<<setw(7)<<item.requesttime<<"        ";
            cout<<setw(7)<<item.arrivetime<<"        ";
            cout<<setw(7)<<item.pcb.waittime<<"        ";
            cout<<setw(7)<<item.get_turnaround_time()<<"            ";
            cout<<setw(4)<<setprecision(3)<<item.get_weighted_turnaround_time()<<"       ";
            cout<<setw(10)<<"DONE"<<endl;
            totaltime += item.get_turnaround_time();
        }
    }
    cout<<"平均周转时间:"<<setprecision(3)<<totaltime/finished.size()<<endl;

}




void Scheduler::show(){

    cout<<"当前时间:"<<timer.gettime();
    cout<<"     所选策略:"<<sche_strategy->strategyname<<endl;
    cout<<"作业——————估计运行时间(分钟)——————还需运行时间——————等待时间——————进程状态——————"<<endl;


    if(!todo.empty()){
        for(auto& item :todo){
            cout<<"job "<<item.pcb.pid<<"     ";
            cout<<setw(7)<<item.requesttime<<"        ";
            cout<<setw(7)<<item.get_need()<<"        ";
            cout<<setw(7)<<item.pcb.waittime<<"        ";
            if(item.pcb.status==READY)
                cout<<setw(10)<<"READY"<<endl;
            else cout<<setw(10)<<"RUNNING"<<endl;
        }
    }
/*
    if(!finished.empty()){
        for(auto& item :finished){
            cout<<"job "<<item.pcb.pid<<"     ";
            cout<<setw(7)<<item.requesttime<<"        ";
            cout<<setw(7)<<item.pcb.finishtime<<"        ";
            cout<<setw(10)<<"DONE"<<endl;
        }
    }*/

}


void Scheduler::check(double now) {

    if(approach.empty())
        return;

    for(auto item = approach.begin();item<approach.end();){
        if(item->arrived(now)){
            //若任务从开始就已经到达
            todo.push_back(*item);
            approach.erase(item);
        }
        else{
            item++;
        }
    }

}