//
// Created by Colin on 7/20/2021.
//

#ifndef PROJECT_PROCESS_H
#define PROJECT_PROCESS_H

class Process {
    public:
        Process(char id, int cpu_burst, int io_burst, int arrival, int num_bursts);
        void change_cpu_burst(int new_time) {cpu_burst_time = new_time; }
        void change_io_burst(int new_time) { io_burst_time = new_time; }
        char get_id() const { return id; }
        int get_cup_burst_time() const { return cpu_burst_time; }
        int get_io_burst_time() const { return io_burst_time; }
        int get_arrival_time() const { return arrival_time; }
        int get_num_cpu_bursts() const { return num_cpu_bursts; }

    private:
        char id;
        int cpu_burst_time;
        int io_burst_time;
        int arrival_time;
        int num_cpu_bursts;
};


#endif //PROJECT_PROCESS_H
