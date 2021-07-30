//
// Created by demo on 7/19/2021.
//

#include <unordered_map>
#include "SJF.h"

/**
 *
 * @param pids
 */
void SJF::process(const std::vector<Process> &pids, double lambda, double alpha) {
    struct co {
        auto operator()(const Process& a, const Process& b) {
            if (a.get_arrival_time() == b.get_arrival_time()) {
                a.get_id() op b.get_id();
            }
            return a.get_arrival_time() op b.get_arrival_time();
        };
    };
    std::priority_queue<Process, std::vector<Process>, co> incomingProcs;
    for (const auto &pid : pids) { incomingProcs.push(pid); }

    // estimation for priority


    int countdowm = 0;
    
    //sort queue by priority
    struct com {
        bool operator()(Process a, Process b) {
            if (a.get_cpu_burst_time() == b.get_cpu_burst_time()) {
                return a.get_arrival_time() op b.get_arrival_time();
            }
            return a.get_cpu_burst_time() op b.get_cpu_burst_time();
        }
    };
    std::priority_queue<Process, std::vector<Process>, com> readyQ;

    cpu.kickProcess();

    IOSystem IOHell;
    int premptiontimer = contextSwitchDur / 2;
    int time = 0;

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


bool processComparator(const Process& a, const Process& b) {
    return false;

};
