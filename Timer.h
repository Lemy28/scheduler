
#ifndef SCHEDULER_TIMER_H
#define SCHEDULER_TIMER_H

#include <iostream>


class Timer {

    double now;

public:
    const double slide;
    const double basetime;

    explicit Timer(double sli);
    double gettime();
    void addtime(double);

};


#endif //SCHEDULER_TIMER_H
