
#include "Strategy.h"


using namespace std;



Strategy* Strategy::get_instance(){
    //选择策略
    cout<<"Select a strategy to run:"<<endl;
    cout<<"1.FCFS "<<endl;
    cout<<"2.SJF "<<endl;
    cout<<"3.RR "<<endl;
    cout<<"4.HRRN "<<endl;
    cout<<"5.SHPF "<<endl;

    int ss;

    Strategy *s = nullptr;

    while (cin>>ss) {
        if(ss == 1){
            s = new FCFS();
            break;
        }
        else if(ss == 2){
            s = new SJF();
            break;
        } else if (ss == 3){
            s = new RR();
            break;
        } else if (ss == 4){
            s = new HRRN();
            break;
        }else if (ss == 5){
            s = new SHPF();
            break;
        }
        cout<<"Try again...."<<endl;
    }

    return s;
}

void Strategy::sort(std::vector<Task> &tasks)
{
    //根据到达时间排序
    std::sort(tasks.begin(), tasks.end(), [](const Task task1,const Task task2) {
        return task1.arrivetime < task2.arrivetime;
    });

};

int Strategy::select(std::vector<Task> &tasks) {

    if (!tasks.empty()){
        //根据不同的调度策略来排序
        sort(tasks);
        return 0;
    }

    //没有任务可以运行
    return -1;

}



void SJF::sort(std::vector<Task> &tasks)  {

    //根据剩余需要服务时间排序
    std::sort(tasks.begin(), tasks.end(), [](const Task &task1,const Task &task2){
        return task1.get_need() < task2.get_need();
    });


}





void SHPF::sort(std::vector<Task> &tasks)  {
    //根据优先级排序
    std::sort(tasks.begin(), tasks.end(), [](const Task &task1,const Task &task2) {
        return task1.static_prio < task2.static_prio;
    });


}


unsigned int RR::index = 0;

//依次返回已到达任务的下标
int RR::select(std::vector<Task> &tasks) {

    if(tasks.empty())
        return -1;


    //避免越界
    index %= tasks.size();
    return index++;



}


double HRRN::get_response_rate (const Task &task) {
    return (task.requesttime+task.pcb.get_waittime())/task.requesttime;
}

void HRRN::sort(std::vector<Task> &tasks) {
    //根据最高响应优先级排序
    std::sort(tasks.begin(), tasks.end(), [this](const Task &task1,const Task &task2) {
        return get_response_rate(task1) < get_response_rate(task2);
    });
}
