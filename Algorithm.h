//
// Created by demo on 7/19/2021.
//

#ifndef PROJECT_ALGORITHM_H
#define PROJECT_ALGORITHM_H

#include <algorithm>
#include "Process.h"
#include "CPU.h"
#include <queue>
#include <utility>
#include "IOSystem.h"

#define op <
#define L 999

/*
 * Singleton would be a good idea, but no time for that
 */
class Algorithm {
protected:
    CPU cpu = CPU();
    unsigned long tick = 0;
    int ctContextSwitch;
    int ctPreemptions;
    int CPUBurstTimes;
    std::queue<Process> incomingProcesses;
    int contextSwitchDur;

public:
    Algorithm(int ctContextSwitch, int ctPreemptions, int cpuBurstTimes, std::queue<Process> incomingProcesses, int contextSwitchDur) :
    ctContextSwitch(ctContextSwitch), ctPreemptions(ctPreemptions), CPUBurstTimes(cpuBurstTimes),
    incomingProcesses(std::move(incomingProcesses)), contextSwitchDur(contextSwitchDur) {};
};


#endif //PROJECT_ALGORITHM_H
