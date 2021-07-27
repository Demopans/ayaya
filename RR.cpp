//
// Created by demo on 7/19/2021.
//

#include "RR.h"

void RR::process(const std::vector<Process> &pids) {
    struct co{
        auto operator()(Process a, Process b){
            if (a.get_arrival_time() == b.get_arrival_time()){
                a.get_id() op b.get_id();
            }
            return a.get_arrival_time() op b.get_arrival_time();
        };
    };
    std::priority_queue<Process,std::vector<Process>,co> ids;
    for (const auto &pid : pids) {ids.push(pid);}

    int countdowm = 0;
    Process t = Process();
    cpu.loadProcess(t);
    int counter = limit;
    while (!ids.empty()){
        // CPU Burst done?


        //recieve process if cpu is idle
        if (cpu.isIdle()){
            Process tmp = ids.top();ids.pop();
            cpu.loadProcess(tmp);
            tick++;
            continue;
        }
        // check if need boot



    }


}
