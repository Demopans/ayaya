//
// Created by demo on 7/19/2021.
//

#include <list>
#include "SJF.h"

void SJF::pushToQueue(const Process &p) {
    this->queue.push(p);
}

/**
 *
 * @param pids
 */
void SJF::process(const std::vector<Process> &pids) {
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

    int countdowm = 0;

    while (true) {
        //boot when empty

        //push to queue if process arrival time
        if (ids.top().get_arrival_time() == tick) {
            pushToQueue(ids.top());
            ids.pop();
        }

        //kick process out if time ends
        Process tmp = cpu.pingProcess();
        bool s = (tick - tmp.get_arrival_time()) == tmp.get_arrival_time();
        if (s) {
            cpu.kickProcess();
        }
    }
}
bool processComparator(Process a, Process b) {
    return false;

};
