//
// Created by demo on 7/19/2021.
//

#include "SRT.h"

bool SRT::compare(const Process& a, const Process& b) {
    if (a.get_cpu_burst_time() == b.get_cpu_burst_time()){
        return a.get_arrival_time() op b.get_arrival_time();
    }
    return a.get_cpu_burst_time() op b.get_cpu_burst_time();
}

void SRT::process(const std::vector<Process>& pids, double lambda, double alpha) {
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
        bool operator()(const Process& a, const Process& b) {
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


}

