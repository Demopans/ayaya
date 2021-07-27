//
// Created by Colin on 7/20/2021.
//

#ifndef PROJECT_PROCESS_H
#define PROJECT_PROCESS_H

class Process {
    public:
        Process();
        Process(char id, int cpu_burst, int io_burst, int arrival, int num_bursts);
        void change_cpu_burst(int new_time) {cpu_burst_time = new_time; }
        void decrement_cpu_burst() { cpu_burst_time--; }
        void change_io_burst();
        void decrement_io_burst() { io_burst_time--; }
        char id() { return id; }
        int cpu_burst_time() { return cpu_burst_time; }
        int io_burst_time() { return io_burst_time; }
        int arrival_time() { return arrival_time; }
        int num_cpu_bursts() { return num_cpu_bursts; }
        void next_cpu_burst();
        void next_io_burst();
        int remaining_bursts();
        void initialize_process();


    private:
        char id;
        int cpu_burst_time;
        int io_burst_time;
        int arrival_time;
        int num_cpu_bursts;
        std::vector<int> cpu_burst_times;
        std::vector<int> io_burst_times;
};


#endif //PROJECT_PROCESS_H
