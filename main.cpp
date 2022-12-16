#include <stdlib.h>
#include <task/PCB.h>
#include <task/Task.h>
#include <vector>
#include "json.hpp"
#include "Strategy.h"
#include "Scheduler.h"
#include <fstream>

using namespace task;


using json = nlohmann::json ;
using namespace std;

void sysinit( vector<Task>& );
vector<Task>* compare();

int main( )
{
    //初始化任务
    vector<Task> tasks{};

    //初始化系统,录入任务到tasks
    sysinit(tasks);
    vector<Task>* tp = &tasks;

    do{
    //选择策略
    Strategy *sp = Strategy::get_instance();

    //将任务载入到调度机中
    Scheduler scheduler = Scheduler(sp,*tp,1);


    //开始调度
    scheduler.start();



    //比较功能
    PCB::reset_counter();
    tp = compare();


    }while(tp);
}



void sysinit(vector<Task> &tasks){

    std::cout<<"<--------------------process schedule simulation--------------------->"<<std::endl;
    std::cout<<"Choose the input way:"<<std::endl;
    cout<<"1. Command Line"<<endl;
    cout<<"2. Deafault input file"<<endl;
    cout<<"3. Quit"<<endl;

    int cmd;
    int prio,arrtime,reqtime;

    cin>>cmd;



    if(cmd==1) {

        cout << "How many processes will be created?" << endl;
        int procount;
        cin >> procount;

        if (procount >= 1) {
            //录入优先级，到达时间，需要消耗的时间

            cout << "---priority(>=0)---arrive time(min)---request time(min)--- "<<endl;

            for (int i = 1; i <= procount; i++) {
                cout << "process " << i << ":";
                cin >> prio;
                cin >> arrtime;
                cin >> reqtime;
                tasks.emplace_back(prio, arrtime, reqtime);
            }
        }

    }
    else if(cmd == 2){
        //读取样例数据并将其转换为json对象
        json json_array;
        ifstream ifs("example.json");
        ifs>>json_array;

        //遍历json对象中的每一个json元素
        for(const auto& it:json_array){
            prio = it["prio"];
            arrtime = it["arrivetime"];
            reqtime = it["requesttime"];
            tasks.emplace_back(prio, arrtime, reqtime);
        }
    }
    else{
        //退出程序
        exit(1);
    }


    //将录入的任务列存储到本地文件中,以便进行比较
    json j;
    ofstream ofs("lastinput.json");

    ofs<<'[';

    for(const auto& task : tasks){
        j["prio"] = task.static_prio;
        j["arrivetime"] = task.arrivetime;
        j["requesttime"] = task.requesttime;
        ofs<<j.dump(4)<<endl;
        if(&task != &tasks.back())
        ofs<<',';
    }
    ofs<<']';

}


vector<Task>* compare(){

    vector<Task>* tp;

    cout<<"Do you need run another strategy to compare? (Y/N)"<<endl;
    char cmd;

    cin>>cmd;


    //需要比较功能
    if(cmd == 'Y'||cmd == 'y'){

        //读取上次运行的数据
        json json_array;
        ifstream ifs("lastinput.json");
        ifs>>json_array;

        int prio,arrtime,reqtime;
        tp = new vector<Task>;

        //遍历json对象中的每一个json元素
        for(const auto& it:json_array){
            prio = it["prio"];
            arrtime = it["arrivetime"];
            reqtime = it["requesttime"];
            tp->emplace_back(prio, arrtime, reqtime);
        }

        //重置计数器

    }
    else{
        //不需要比较功能
        tp = nullptr;
    }


    return tp;

}