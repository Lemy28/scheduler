
#include "Timer.h"

Timer::Timer(double sli):slide(sli),basetime(0),now(0){
}


double Timer::gettime() {
    return now;
}

void Timer::addtime(double cost) {
    if(cost>0)
    now+=cost;
}