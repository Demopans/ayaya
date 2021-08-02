//
// Created by Colin on 7/20/2021.
//

#ifndef PROJECT_PROCESS_H
#define PROJECT_PROCESS_H

#include "Random.h"
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <fstream>
#include <iomanip>

const char id_names[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', \
                            'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', \
                            'X', 'Y', 'Z'};

class Process {

    private:
        char id;
        int cpu_burst_time;
        int original_burst_time;
        int total_cpu_burst_time;
        int io_burst_time;
        int arrival_time;
        int num_cpu_bursts;
        int remaining_bursts;
        std::vector<int> cpu_burst_times;
        std::vector<int> estimated_cpu_burst_times;
        std::vector<int> io_burst_times;
        bool empty_process;
        int tau;
        int remaining_tau;

    public:
        Process() { empty_process = true; }
        Process(char id, int arrival_time, const std::vector<int>& cpu_bursts, \
                const std::vector<int>& io_bursts, double alpha, double lambda);
        void decrement_cpu_burst() { cpu_burst_time--; }
        void decrement_io_burst() { io_burst_time--; }
        void increment_cpu_burst() { cpu_burst_time++; }
        void decrement_tau() { remaining_tau--; }
        void increment_tau() { remaining_tau++; }
        char get_id() const { return id; }
        int get_original_time() const { return original_burst_time; }
        int get_cpu_burst_time() const { return cpu_burst_time; }
        int get_total_cpu_burst_time() const { return total_cpu_burst_time; }
        int get_io_burst_time() const { return io_burst_time; }
        int get_arrival_time() const { return arrival_time; }
        int get_num_cpu_bursts() const { return num_cpu_bursts; }
        void next_burst_times();
        void next_tau() { tau = estimated_cpu_burst_times[num_cpu_bursts - remaining_bursts]; remaining_tau = tau; }
        int get_remaining_bursts() const { return remaining_bursts; }
        bool is_empty() const { return empty_process; }
        int get_tau() const { return tau; }
        int get_remaining_tau() const { return remaining_tau; }
        std::vector<int> get_cpu_burst_times() { return cpu_burst_times; }
        std::vector<int> get_io_burst_times() { return io_burst_times; }
};

bool operator<(const Process& a, const Process& b);

void initialize_processes(int num_processes, int seed, double lambda, int upper_bound, \
                          std::vector<Process>& processes, double alpha);
void erase_process(std::vector<Process>& processes, char id);
bool contains(const std::vector<Process>& io_queue, char id);
std::string queue_string(std::queue<Process> q);
std::string pqueue_string(std::priority_queue<Process> q);
void write_output(const std::string& algo_name, double avg_cpu_burst, double avg_wait_time, \
                  double avg_turnaround_time, int num_context_switches, int num_preemptions, \
                  double cpu_utilization);


#endif //PROJECT_PROCESS_H
