//
// Created by Colin on 7/20/2021.
//

#include "Process.h"

Process::Process(char id, int arrival_time, std::vector<int> cpu_bursts, std::vector<int> io_bursts) {
	//Initialize all the parameters that can be set 
	this->empty_process = false;
	this->id = id;
	this->arrival_time = arrival_time;
	this->num_cpu_bursts = cpu_bursts.size();
	for(int a = 0; a < num_cpu_bursts; a++) {
		this->cpu_burst_times.push_back(cpu_bursts[a]);
	}
	for(int b = 0; b < io_bursts.size(); b++) {
		this->io_burst_times.push_back(io_bursts[b]);
	}
	this->remaining_bursts = num_cpu_bursts;
	this->cpu_burst_time = this->cpu_burst_times[0];
}

void Process::next_burst_times() {
	remaining_bursts--;
	cpu_burst_time = cpu_burst_times[num_cpu_bursts - remaining_bursts];
	if(remaining_bursts != 0) io_burst_time = io_burst_times[num_cpu_bursts - remaining_bursts - 1];
}

void erase_process(std::vector<Process>& processes, char id) {
	for(int i = 0; i < processes.size(); i++) {
		if(processes[i].get_id() == id) {
			processes.erase(processes.begin() + i);
		}
	}
}

bool contains(const std::vector<Process>& io_queue, char id) {
	for(int i = 0; i < io_queue.size(); i++) {
		if(io_queue[i].get_id() == id) return true;
	}
	return false;
}


