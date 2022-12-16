
#include <task/Task.h>
using namespace task;


double Task::get_need() const {

    double need = requesttime-pcb.get_servicetime();
    return need<=0?0:need;

}

bool Task::arrived(double curtime) {
    
    return arrivetime<=curtime;

}