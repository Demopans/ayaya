//
// Created by demo on 7/19/2021.
//

#ifndef PROJECT_RR_H
#define PROJECT_RR_H

#include <utility>

#include "Algorithm.h"
#include "IOSystem.h"

class RR : private Algorithm {
public:
    void process(const std::vector<Process> &pids);

    RR(int ctContextSwitch, int ctPreemptions, int cpuBurstTimes, const std::queue<Process> &incomingProcesses,
       int limit, int contextSwitchDur) : Algorithm(ctContextSwitch, ctPreemptions, cpuBurstTimes, incomingProcesses, contextSwitchDur), limit(limit) {}

private:
    int limit;
};


#endif //PROJECT_RR_H
