//
// Created by demo on 7/19/2021.
//

#ifndef PROJECT_SJF_H
#define PROJECT_SJF_H

#include <algorithm>
#include <queue>
#include "Algorithm.h"
#include "Process.h"
#include "CPU.h"



/*
 * Singleton would be a good idea, bur no time for that
 */
class SJF : private Algorithm{
private:
    static bool eventComparator(Process a, Process b);
    struct com{
        bool operator()(Process a, Process b){return eventComparator(a,b);}
    };

    std::priority_queue<Process,std::vector<Process>,com> queue;
    CPU core = CPU();
public:
    void process();
    void pushToQueue(Process &p);

};


#endif //PROJECT_SJF_H
