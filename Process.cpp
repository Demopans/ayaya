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
	this->total_cpu_burst_time = 0;
	for(int a = 0; a < num_cpu_bursts; a++) {
		this->total_cpu_burst_time += cpu_bursts[a];
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

std::string queue_string(std::queue<Process> q) {
	std::string result = "[Q ";
	if(q.empty()) return result + "empty]";
	while(!q.empty()) {
		result += q.front().get_id();
		q.pop();
	}
	result += "]";
	return result;
}

void write_output(const std::string& algo_name, double avg_cpu_burst, double avg_wait_time, \
                  double avg_turnaround_time, int num_context_switches, int num_preemptions, \
                  double cpu_utilization) {
	std::ofstream simfile;
	if(algo_name == "FCFS") simfile.open("simout.txt");
	else simfile.open("simout.txt", std::ios_base::app);
	simfile << "Algorithm " + algo_name << std::endl;
	simfile << "-- average CPU burst time: " << std::fixed << std::setprecision(3) << avg_cpu_burst << " ms" << std::endl;
	simfile << "-- average wait time: " << std::fixed << std::setprecision(3) << avg_wait_time << " ms" << std::endl;
	simfile << "-- average turnaround time: " << std::fixed << std::setprecision(3) << avg_turnaround_time << " ms" << std::endl;
	simfile << "-- total number of context switches: " << num_context_switches << std::endl;
	simfile << "-- total number of preemptions: " << num_preemptions << std::endl;
	simfile << "-- CPU utilization: " << std::fixed << std::setprecision(3) << cpu_utilization << "%" << std::endl;
}
