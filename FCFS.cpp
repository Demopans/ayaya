#include "FCFS.h"

void FCFS(int num_processes, int seed, int context_switch, double lambda, int upper_bound) {
	std::vector<Process> processes;
	std::vector<Process> io_queue;
	std::queue<Process> ready_queue;
	Process running_process = Process();
	initialize_processes(num_processes, seed, lambda, upper_bound, processes, 0);
	int total_cpu_burst_time = 0;
	int total_num_bursts = 0;
	int wait_time = 0;
	for(int b = 0; b < int(processes.size()); b++) {
		total_cpu_burst_time += processes[b].get_total_cpu_burst_time();
		total_num_bursts += processes[b].get_num_cpu_bursts();
	}
	double avg_cpu_burst = double(total_cpu_burst_time)/total_num_bursts;
	int num_context_switches = 0;
	int running_cpu_bursts = 0;
	int t = 0;
	int t_cs = context_switch;
	bool doing_context_switch = false;
	std::cout << "time 0ms: Simulator started for FCFS [Q empty]" << std::endl;
	while(!processes.empty()) {
		//Check if there is a running process
		if(!running_process.is_empty()) {
			//Check if the running process has ended its CPU burst
			if(running_process.get_cpu_burst_time() == 0) doing_context_switch = true;
			if(doing_context_switch) {
				if(t_cs == context_switch) {
					num_context_switches++;
					running_process.next_burst_times();
					if(running_process.get_remaining_bursts() > 0) {
						if(t < 1000) {
							std::cout << "time " << t << "ms: ";
							std::cout << "Process " << running_process.get_id() << " completed a CPU burst; ";
							std::cout << running_process.get_remaining_bursts();
							if(running_process.get_remaining_bursts() == 1) std::cout << " burst to go ";
							else std::cout << " bursts to go ";
							std::cout << queue_string(ready_queue) << std::endl;

							std::cout << "time " << t << "ms: ";
							std::cout << "Process " << running_process.get_id() << " switching out of CPU; ";
							std::cout << "will block on I/O until time " << t + running_process.get_io_burst_time() + context_switch;
							std::cout << "ms " << queue_string(ready_queue) << std::endl;
						}	
					}
					else {
						std::cout << "time " << t << "ms: ";
						std::cout << "Process " << running_process.get_id() << " terminated ";
						std::cout << queue_string(ready_queue) << std::endl;
					}
				}
				t_cs--;
				if(t_cs < 0) {
					t_cs = context_switch;
					doing_context_switch = false;
					if(running_process.get_remaining_bursts() == 0) {
						erase_process(processes, running_process.get_id());
					}
					else {
						io_queue.push_back(running_process);
					}
					running_process = Process();
				}
			}
			else {
				running_process.decrement_cpu_burst();
				running_cpu_bursts++;
			}
		}
		//Check if there is no running process
		else {
			if(!ready_queue.empty()) {
				t_cs--;
				if(t_cs <= 0) {
					running_process = ready_queue.front();
					ready_queue.pop();
					t_cs = context_switch;
					if(t < 1000) {
						std::cout << "time " << t << "ms: ";
						std::cout << "Process " <<  running_process.get_id() << " started using ";
						std::cout << "the CPU for " << running_process.get_cpu_burst_time();
						std::cout << "ms burst " << queue_string(ready_queue) << std::endl; 
					}
					running_process.decrement_cpu_burst();
					running_cpu_bursts++;
				}
			}
		}
		

		//Run the processes doing I/O in alphabetical order
		for(int j = 0; j < int(processes.size()); j++) {
			for(int k = 0; k < int(io_queue.size()); k++)  {
				if(io_queue[k].get_id() == processes[j].get_id()) {
					if(io_queue[k].get_io_burst_time() == 0) {
						ready_queue.push(io_queue[k]);
						if(t < 1000) {
							std::cout << "time " << t << "ms: ";
							std::cout << "Process " << io_queue[k].get_id() << " completed I/O; ";
							std::cout << "added to ready queue " << queue_string(ready_queue) << std::endl;
						}	
						erase_process(io_queue, io_queue[k].get_id());
					}
					else {
						io_queue[k].decrement_io_burst();
					}
				}
			}
		}

		//Check for arriving processes
		for(int i = 0; i < int(processes.size()); i++) {
			if(processes[i].get_arrival_time() == t) {
				ready_queue.push(processes[i]);
				if(t < 1000) {
					std::cout << "time " << t << "ms: ";
					std::cout << "Process " << processes[i].get_id() << " arrived; added to ready queue ";
					std::cout << queue_string(ready_queue) << std::endl;
				}
			}
		}
		if(processes.empty()) {
			std::cout << "time " << t << "ms: ";
			std::cout << "Simulator ended for FCFS [Q empty]" << std::endl;
		}
		//Increment the timer
		t++;

		//Increase the wait time for every process in the ready queue, not 
		//including the process doing a context switch
		if(running_process.is_empty()) {
			if(ready_queue.size() > 0) {
				wait_time += (ready_queue.size() - 1);
			}
		}
		//Not doing a context switch, include every process in the ready queue
		else {
			wait_time += ready_queue.size();
		}
	}
	double average_wait_time = double(wait_time)/total_num_bursts;
	int total_turnaround_time = wait_time + num_context_switches * 2 * context_switch + total_cpu_burst_time;
	double avg_turnaround_time = double(total_turnaround_time)/total_num_bursts;
	double cpu_utilization = double(running_cpu_bursts * 100)/(t - 1);
	write_output("FCFS", avg_cpu_burst, average_wait_time, avg_turnaround_time, \
				num_context_switches, 0, cpu_utilization);
}