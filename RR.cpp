//
// Created by demo on 7/19/2021.
//

#include "RR.h"
bool cc(Process a, Process b) {
    if (a.get_io_burst_time() == b.get_io_burst_time()) {
        a.get_id() op b.get_id();
    }
    return a.get_io_burst_time() op b.get_io_burst_time();
};

void RR::process(const std::vector<Process> &pids) {
    struct co {
        auto operator()(Process a, Process b) {
            if (a.get_arrival_time() == b.get_arrival_time()) {
                a.get_id() op b.get_id();
            }
            return a.get_arrival_time() op b.get_arrival_time();
        };
    };
    std::priority_queue<Process, std::vector<Process>, co> ids;
    for (const auto &pid : pids) { ids.push(pid); }

    std::queue<Process> readyQ;
    for (const auto &item : pids) {readyQ.push(item);}

    std::vector<Process> IOHell;


    int premptiontimer = 0;
    int time = 0;
    int timer = limit;

    while (!ids.empty()) {
        Process t;
        // CPU Burst done?
        if (!cpu.isIdle()&&premptiontimer==0){
            t = cpu.pingProcess();
            if (t.get_cpu_burst_time()==0) {
                t = cpu.kickProcess();
                IOHell.push_back(t);
                std::push_heap(IOHell.begin(),IOHell.end(),cc);
                premptiontimer = contextSwitchDur;
            } else if (timer==0){
                if (!readyQ.empty()){
                    t = cpu.kickProcess();
                    readyQ.push(t);
                }
                else{
                    timer = limit;
                }

            }
            else if (t.get_cpu_burst_time()>0){
                cpu.subCPUTime();
            }
        }

        //io hell
        while ((t = IOHell.front()).get_io_burst_time()==0){
            std::pop_heap(IOHell.begin(),IOHell.end(),cc);
            //check if cpu time remains
            if (t.get_cpu_burst_time()>0){
                readyQ.push(t);
            }
        }
        for (auto &item : IOHell) {item.decrement_io_burst();}

        //receive process if cpu is idle
        if (cpu.isIdle()) {
            t = ids.top();
            ids.pop();
            cpu.loadProcess(t);
            tick++;
            continue;
        }
        // check if need boot
        time++;timer--;
    }


}
