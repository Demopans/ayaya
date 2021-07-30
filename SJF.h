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

    struct com {
        bool operator()(Process a, Process b) {
            if (a.get_cpu_burst_time() == b.get_cpu_burst_time()) {
                return a.get_arrival_time() op b.get_arrival_time();
            }
            return a.get_cpu_burst_time() op b.get_cpu_burst_time();
        }
    };

    std::priority_queue<Process, std::vector<Process>, com> queue;

    void pushToQueue(const Process &p);

public:
    SJF(int ctContextSwitch, int ctPreemptions, int cpuBurstTimes, const std::queue<Process> &incomingProcesses,
        std::priority_queue<Process, std::vector<Process>, com> queue, int contextSwitchDur) :
            Algorithm(ctContextSwitch, ctPreemptions, cpuBurstTimes, incomingProcesses, contextSwitchDur), queue(std::move(queue)) {}

    void process(const std::vector<Process> &pids);

};
bool processComparator(Process a, Process b);

#endif //PROJECT_SJF_H
