//
// Created by demo on 7/19/2021.
//

#include "RR.h"

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

    struct cio {
        auto operator()(Process a, Process b) {
            if (a.get_io_burst_time() == b.get_io_burst_time()) {
                a.get_id() op b.get_id();
            }
            return a.get_io_burst_time() op b.get_io_burst_time();
        };
    };
    std::priority_queue<Process, std::vector<Process>, cio> IOHell;


    int countdowm = 0;
    int counter = limit;

    int time = 0;
    while (!ids.empty()) {
        Process t;
        // CPU Burst done?
        if (!cpu.isIdle() && (t = cpu.pingProcess()).get_cpu_burst_time()==0) {
            t = cpu.kickProcess();
            IOHell.push(t);
        }
        else if (t.get_cpu_burst_time()>0){
            cpu.subCPUTime();
        }
        //io hell
        while ((t = IOHell.top()).get_io_burst_time()==0){
            IOHell.pop();
            //check if cpu time remains
            if (t.get_cpu_burst_time()>0){
                readyQ.push(t);
            }
        }

        //receive process if cpu is idle
        if (cpu.isIdle()) {
            Process tmp = ids.top();
            ids.pop();
            cpu.loadProcess(tmp);
            tick++;
            continue;
        }
        // check if need boot


        time++;
    }


}
