//
// Created by demo on 7/19/2021.
//

#ifndef PROJECT_SJF_H
#define PROJECT_SJF_H

#include <algorithm>
#include <queue>
#include <utility>
#include "Algorithm.h"
#include "Process.h"

#include "CPU.h"


class SJF : private Algorithm {
private:


public:
    SJF(int ctContextSwitch, int ctPreemptions, int cpuBurstTimes, const std::queue<Process> &incomingProcesses,
        int contextSwitchDur): Algorithm(ctContextSwitch, ctPreemptions, cpuBurstTimes, incomingProcesses,
                                         contextSwitchDur) {}

    void process(const std::vector<Process> &pids);

};
bool processComparator(const Process& a, const Process& b);

#endif //PROJECT_SJF_H
