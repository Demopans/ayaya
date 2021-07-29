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

void initialize_processes(int num_processes, int seed, double lambda, int upper_bound, \
 						  std::vector<Process>& processes) {
	//Set the seed
	srand48(seed);
	//Iterator for each process, starting from process "A"
	for(int i = 0; i < num_processes; i++) {
		char pid = id_names[i];
		std::vector<int> cpu_bursts;
		std::vector<int> io_bursts;
		int arrival_time = (int) next_exp(lambda, upper_bound);
		int num_cpu_bursts = int(drand48() * 100) + 1;
		for(int j = 0; j < num_cpu_bursts; j++) {
			cpu_bursts.push_back((int(next_exp(lambda, upper_bound))) + 1);
			if(j != num_cpu_bursts - 1) {
				io_bursts.push_back( ((int(next_exp(lambda, upper_bound))) + 1) * 10);
			}
		}
		Process init_process(pid, arrival_time, cpu_bursts, io_bursts);
		processes.push_back(init_process);

	}
}
