//
// Created by demo on 7/19/2021.
// Highly suggest using an IDE for code review
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
    std::priority_queue<Process, std::vector<Process>, co> incomingProcs;
    for (const auto &pid : pids) { incomingProcs.push(pid); }

    std::queue<Process> readyQ;
    for (const auto &item : pids) { readyQ.push(item); }

    IOSystem IOHell;


    int premptiontimer = contextSwitchDur / 2;
    int time = 0;
    int timer = limit;

    cpu.kickProcess();

    while (!incomingProcs.empty()) {//starts on empty queue
        Process t;
        if (premptiontimer == 0) {//cpu
            //cpu burst finished
            if (cpu.pingProcess().get_cpu_burst_time()==0){
                t = cpu.kickProcess();
                if (t.get_remaining_bursts()>0){
                    //to io
                    IOHell.pushIntoIO(t);
                }
                else{
                    // print finished
                }
                premptiontimer=contextSwitchDur;
            }
        }

        //run io checks
        if ((t = IOHell.pingTop()).get_io_burst_time()==0){
            if (t.get_remaining_bursts()>0){
                IOHell.pop();
                readyQ.push(t);
            }
            else{
                IOHell.pop();
            }
        }

        //check for arrivals
        if ((t=incomingProcs.top()).get_arrival_time()==time){
            incomingProcs.pop();
            readyQ.push(t);
        }

        premptiontimer = premptiontimer > 0 ? --premptiontimer : premptiontimer;
        time++;
    }


}
