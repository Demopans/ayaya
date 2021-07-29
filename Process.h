//
// Created by Colin on 7/20/2021.
//

#ifndef PROJECT_PROCESS_H
#define PROJECT_PROCESS_H

#include <vector>
#include "Random.h"
#include <iostream>

class Process {

    private:
        char id = -1;
        int cpu_burst_time;
        int io_burst_time;
        int arrival_time;
        int num_cpu_bursts;
        int remaining_bursts;
        std::vector<int> cpu_burst_times;
        std::vector<int> io_burst_times;


    public:
        Process()= default;//subisture to null
        Process(char id, int arrival_time, std::vector<int> cpu_bursts, std::vector<int> io_bursts);
        void change_cpu_burst(int new_time) {cpu_burst_time = new_time; }
        void decrement_cpu_burst() { cpu_burst_time--; }
        void change_io_burst();
        void decrement_io_burst() { io_burst_time--; }
        char get_id() { return id; }
        int get_cpu_burst_time() const { return cpu_burst_time; }
        int get_io_burst_time() const { return io_burst_time; }
        int get_arrival_time() const { return arrival_time; }
        int get_num_cpu_bursts() const { return num_cpu_bursts; }
        void next_cpu_burst();
        void next_io_burst();
        int get_remaining_bursts() const { return remaining_bursts; }
        std::vector<int> get_cpu_burst_times() { return cpu_burst_times; }
        std::vector<int> get_io_burst_times() { return io_burst_times; }
};


#endif //PROJECT_PROCESS_H
