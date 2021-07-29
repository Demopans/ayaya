//
// Created by Colin on 7/20/2021.
//

#ifndef PROJECT_PROCESS_H
#define PROJECT_PROCESS_H

#include <vector>
#include "Random.h"
#include <iostream>

const char id_names[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', \
                            'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', \
                            'X', 'Y', 'Z'};

class Process {

    private:
        char id;
        int cpu_burst_time;
        int io_burst_time;
        int arrival_time;
        int num_cpu_bursts;
        int remaining_bursts;
        std::vector<int> cpu_burst_times;
        std::vector<int> io_burst_times;


    public:
        Process();
        Process(char id, int arrival_time, std::vector<int> cpu_bursts, std::vector<int> io_bursts);
        void change_cpu_burst(int new_time) {cpu_burst_time = new_time; }
        void decrement_cpu_burst() { cpu_burst_time--; }
        void change_io_burst();
        void decrement_io_burst() { io_burst_time--; }
        char get_id() { return id; }
        int get_cpu_burst_time() { return cpu_burst_time; }
        int get_io_burst_time() { return io_burst_time; }
        int get_arrival_time() { return arrival_time; }
        int get_num_cpu_bursts() { return num_cpu_bursts; }
        void next_cpu_burst();
        void next_io_burst();
        int get_remaining_bursts() { return remaining_bursts; }
        std::vector<int> get_cpu_burst_times() { return cpu_burst_times; }
        std::vector<int> get_io_burst_times() { return io_burst_times; }
};

void initialize_processes(int num_processes, int seed, double lambda, int upper_bound, \
                          std::vector<Process>& processes);


#endif //PROJECT_PROCESS_H
