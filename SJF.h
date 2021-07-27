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

#define op <


/*
 * Singleton would be a good idea, bur no time for that
 */
class SJF : private Algorithm{
private:
    int contextSwitch = 0;

    struct com{
        bool operator()(Process a, Process b){
            if (a.get_cup_burst_time() == b.get_cup_burst_time()){return a.get_arrival_time() op b.get_arrival_time();}
            return a.get_cup_burst_time() op b.get_cup_burst_time();
        }
    };

    std::priority_queue<Process,std::vector<Process>,com> queue;
    CPU core = CPU();

    void pushToQueue(const Process &p);
public:
    void process(const std::vector<Process> &pids);

};


#endif //PROJECT_SJF_H
