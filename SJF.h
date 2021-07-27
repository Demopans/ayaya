//
// Created by demo on 7/19/2021.
//

#ifndef PROJECT_SJF_H
#define PROJECT_SJF_H

#include <algorithm>
#include <queue>
#include "Algorithm.h"
#include "Process.h"

bool processComparator(Process a, Process b);

class SJF : private Algorithm{
    std::priority_queue<Process> queue;
};


#endif //PROJECT_SJF_H
