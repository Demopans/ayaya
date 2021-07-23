//
// Created by demo on 7/19/2021.
//

#ifndef PROJECT_ALGORITHM_H
#define PROJECT_ALGORITHM_H

#include <algorithm>
#include "Process.h"
#include "CPU.h"
#include <queue>

class Algorithm {
public:

private:
    static int ctContextSwitch;
    static int ctPreemptions;
    static int CPUBurstTimes;
    static std::queue<Process> incomingProcesses;
    CPU cpu;

};


#endif //PROJECT_ALGORITHM_H
