//
// Created by demo on 7/19/2021.
//

#ifndef PROJECT_EVENT_H
#define PROJECT_EVENT_H

#include "Event.h"

typedef enum {
    NOT_YET_ARRIVED, READY, RUNNING, BLOCKED, FINISHED
} processState;

typedef enum {
    NO_BURST, IO_BURST, CPU_BURST, CX_ON, CX_OFF
} burstType;

class Event {
public:
    char id;
    int t_arrive;
    int num_cpu_burst;
    int counter_cpu_burst;
    burst_type current_burst_type;
    int current_burst_start;
    int current_burst_start_overall;
    int queue_entry_time;
    bool cpu_burst_preempted;
    int **burst;
    int tau = 0;
    int next_tau;  //SRT need it to calculate tau
    int TAT;
    int WT;
    process_state state;
    Event() = default;
    int x;
};


#endif //PROJECT_EVENT_H
