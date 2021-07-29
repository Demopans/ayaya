#include "Process.h"
#include "Random.h"
#include <vector>
#include <string>
#include <queue>

double next_exp(double lambda, int upper_bound);

void FCFS(std::vector<Process> processes, int context_switch) {
	std::string output;
	std::vector<Process> io_queue;
	std::queue<Process> ready_queue;
	Process running_process;
	int t = 0;
	int t_cs = context_switch;
	int cpu_not_utilized = 0;
	int preemptions = 0;
	bool starting_context_switch = false;
	while(!processes.empty()) {
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
						processes.remove(running_process);
					}
					else {
						io_queue.push(running_process);
						running_process.next_cpu_burst();
					}
					running_process = ready_queue.front();
					ready_queue.pop();
				}
			}
			else {
				if(running_process.get_remaining_bursts() == 0) {
					processes.remove(running_process);
				}
				else {
					io_queue.push(running_process);
					running_process.next_cpu_burst();
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

		//Run the processes doing I/O
		for(int j = 0; j < io_queue.size(); j++) {
			if(io_queue[j].get_io_burst_time() == 0) {
				io_queue[j].next_io_burst();
				ready_queue.push(io_queue[j]);
				io_queue.remove(j);
			}
			else {
				io_queue[j].decrement_cpu_burst();
			}
		}

		//Check for arriving processes
		for(auto & processe : processes) {
			if(processe.get_arrival_time() == t) {
				//Check if it arrives with the ready queue empty
				if(ready_queue.empty()) {
					running_process = processe;
				}
				else {
					ready_queue.push(running_process);
				}
			}
		}

	}

}