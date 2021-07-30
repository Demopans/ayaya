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
        int cpu_burst_time{};
        int io_burst_time{};
        int arrival_time{};
        int num_cpu_bursts{};
        int remaining_bursts{};
        std::vector<int> cpu_burst_times;
        std::vector<int> io_burst_times;
        bool empty_process;

    public:
        Process() { empty_process = true; }

        Process(char id, int arrival_time, std::vector<int> cpu_bursts, std::vector<int> io_bursts);
        void change_cpu_burst(int new_time) {cpu_burst_time = new_time; }
        void decrement_cpu_burst() { cpu_burst_time--; }
        void change_io_burst();
        void decrement_io_burst() { io_burst_time--; }
        char get_id() const { return id; }
        int get_cpu_burst_time() const { return cpu_burst_time; }
        int get_io_burst_time() const { return io_burst_time; }
        int get_arrival_time() const { return arrival_time; }
        int get_num_cpu_bursts() const { return num_cpu_bursts; }
        void next_burst_times();
        int get_remaining_bursts() const { return remaining_bursts; }
        bool is_empty() const { return empty_process; }
        std::vector<int> get_cpu_burst_times() { return cpu_burst_times; }
        std::vector<int> get_io_burst_times() { return io_burst_times; }
};

void erase_process(std::vector<Process>& processes, char id);
bool contains(const std::vector<Process>& io_queue, char id);

#endif //PROJECT_PROCESS_H
