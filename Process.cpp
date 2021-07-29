//
// Created by Colin on 7/20/2021.
//

#include "Process.h"

Process::Process(char id, int arrival_time, std::vector<int> cpu_bursts, std::vector<int> io_bursts) {
	//Initialize all the parameters that can be set 
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
	if(num_cpu_bursts > 1) this->io_burst_time = io_bursts[0];
}


