#include "FCFS.h"

#include <utility>

void FCFS(std::vector<Process> pids, int context_switch) {
	std::string output;
	std::vector<Process> processes = std::move(pids);
	std::vector<Process> io_queue;
	std::queue<Process> ready_queue;
	Process running_process = Process();

	int t = 0;
	int t_cs = context_switch;
	int cpu_not_utilized = 0;
	int preemptions = 0;
	bool starting_context_switch = false;
	std::cout << "time 0ms: Simulator started for FCFS [Q empty]" << std::endl;
	while(!processes.empty()) {
		if(!running_process.is_empty()) {
			//Check if the running process has ended its CPU burst
			if(running_process.get_cpu_burst_time() == 0) {
				if(!ready_queue.empty()) {
					if(t_cs != 0) {
						t_cs--;
					}
					else {
						starting_context_switch = true;
						t_cs = context_switch;
						if(running_process.get_remaining_bursts() == 0) {
							erase_process(processes, running_process.get_id());
						}
						else {
							io_queue.push_back(running_process);
							running_process.next_burst_times();
						}
						running_process = ready_queue.front();
						ready_queue.pop();
					}
				}
				else {
					if(running_process.get_remaining_bursts() == 0) {
						std::cout << "Process " << running_process.get_id() << "terminated" << std::endl;
						erase_process(processes, running_process.get_id());
					}
					else {
						io_queue.push_back(running_process);
						running_process.next_burst_times();
						running_process = Process();
					}
				}
			}
			//Run 1ms of running process if context switch is done
			else {
				if(starting_context_switch) {
					if(t_cs != 0) {
						t_cs--;
					}
					else {
						starting_context_switch = false;
						t_cs = context_switch;
					}
				}
				else {
					running_process.decrement_cpu_burst();
				}
			}
		}
		

		//Run the processes doing I/O in alphabetical order
		for(int j = 0; j < processes.size(); j++) {
			if(contains(io_queue, processes[j].get_id())) {
				if(io_queue[j].get_io_burst_time() == 0) {
					ready_queue.push(io_queue[j]);
					erase_process(io_queue, io_queue[j].get_id());
				}
				else {
					io_queue[j].decrement_cpu_burst();
				}
			}
		}

		//Check for arriving processes
		for(int i = 0; i < processes.size(); i++) {
			if(processes[i].get_arrival_time() == t) {
				ready_queue.push(processes[i]);
				std::cout << "Process " << processes[i].get_id() << " arrived; added to ready queue" << std::endl;
			}
		}
		t++;
	}
}