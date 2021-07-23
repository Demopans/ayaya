//
// Created by demo on 7/19/2021.
//

#ifndef PROJECT_SJF_H
#define PROJECT_SJF_H

#include <algorithm>
#include <queue>
#include "Algorithm.h"
#include "Process.h"

bool eventComparator(Process a, Process b);
struct com{
    bool operator()(Process a, Process b){return eventComparator(a,b);}
};

class SJF : private Algorithm{
    std::priority_queue<Process,std::vector<Process>,com> queue;

};


#endif //PROJECT_SJF_H
