//
// Created by Colin on 7/20/2021.
//

#ifndef PROJECT_PROCESS_H
#define PROJECT_PROCESS_H

class Process {
public:
    Process() = default;

    Process(char id, int cpuBurstTime, int ioBurstTime, int arrivalTime, int numCpuBursts, int state) :
            id(id),cpu_burst_time(cpuBurstTime),io_burst_time(ioBurstTime),
            arrival_time(arrivalTime),num_cpu_bursts(numCpuBursts),state(state) {}

    explicit Process(char id) : id(id) {}

    void change_cpu_burst(int new_time) {cpu_burst_time = new_time; }
    void change_io_burst(int new_time) { io_burst_time = new_time; }
    char get_id() const { return id; }
    int get_cup_burst_time() const { return cpu_burst_time; }
    int get_io_burst_time() const { return io_burst_time; }
    int get_arrival_time() const { return arrival_time; }
    int get_num_cpu_bursts() const { return num_cpu_bursts; }

private:
    char id;
    int cpu_burst_time = -1;
    int io_burst_time = -1;
    int arrival_time = -1;
    int num_cpu_bursts = -1;
    int state = -1; // running: 2, ready: 1, waiting: 0
};


#endif //PROJECT_PROCESS_H
