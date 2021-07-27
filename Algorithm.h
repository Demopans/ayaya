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

class Algorithm {
private:
    struct cmp{
        bool operator()(Process a, Process b){
            return (a.get_io_burst_time() == b.get_io_burst_time())?
                   (a.get_id()>b.get_id()):
                   (a.get_io_burst_time() > b.get_io_burst_time());
        }
    };
    std::priority_queue<Process, std::vector<Process>,cmp> IOstuck;

protected:
    CPU cpu = CPU();
    unsigned long tick = 0;
    int ctContextSwitch;
    int ctPreemptions;
    int CPUBurstTimes;
    std::queue<Process> incomingProcesses;


public:
    Algorithm(int ctContextSwitch, int ctPreemptions, int cpuBurstTimes, std::queue<Process> incomingProcesses) :
    ctContextSwitch(ctContextSwitch), ctPreemptions(ctPreemptions), CPUBurstTimes(cpuBurstTimes),
    incomingProcesses(std::move(incomingProcesses)) {};
};


#endif //PROJECT_ALGORITHM_H
