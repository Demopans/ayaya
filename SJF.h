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

bool eventComparator(Process a, Process b);
struct com{
    bool operator()(Process a, Process b){return eventComparator(a,b);}
};

class SJF : private Algorithm{
private:
    std::priority_queue<Process,std::vector<Process>,com> queue;

public:
    void oneRound();
    void pushToQueue(Process &p);

};


#endif //PROJECT_SJF_H
