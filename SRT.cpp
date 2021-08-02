//
// Created by Colin on 8/2/2021.
//

#include "SRT.h"


void SRT(int num_processes, int seed, int context_switch, double lambda, int upper_bound, double alpha) {
    std::vector<Process> processes;
    std::vector<Process> io_queue;
    std::priority_queue<Process> ready_queue;
    std::vector<Process> ready_queue_wait;
    Process running_process = Process();
    Process switch_process = Process();
    initialize_processes(num_processes, seed, lambda, upper_bound, processes, alpha);
    int total_cpu_burst_time = 0;
    int total_num_bursts = 0;
    int wait_time = 0;
    int preemptions = 0;
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
    int prev_tau;
    bool doing_switch = false;
    bool doing_preemption = false;
    std::cout << "time 0ms: Simulator started for SRT [Q empty]" << std::endl;
    while(!processes.empty()) {
        //Check if there is a running process
        if(!running_process.is_empty()) {
            //Check if the running process has ended its CPU burst
            if(running_process.get_cpu_burst_time() == 0 || doing_preemption) 
                doing_context_switch = true;
            if(doing_context_switch) {
                if(t_cs == context_switch) {
                    num_context_switches++;
                    if(!doing_preemption) {
	                    running_process.next_burst_times();
	                    prev_tau = running_process.get_tau();
	                    if(running_process.get_remaining_bursts() > 0) {
	                        if(t < 1000) {
	                            std::cout << "time " << t << "ms: ";
	                            std::cout << "Process " << running_process.get_id() << " (tau " << running_process.get_tau();
	                            std::cout << "ms) completed a CPU burst; " << running_process.get_remaining_bursts();
	                            if(running_process.get_remaining_bursts() == 1) std::cout << " burst to go ";
	                            else std::cout << " bursts to go ";
	                            std::cout << pqueue_string(ready_queue) << std::endl;
	                        }
	                        running_process.next_tau();
	                        if(t < 1000) {
	                            std::cout << "time " << t << "ms: ";
	                            std::cout << "Recalculated tau from " << prev_tau << "ms to " << running_process.get_tau();
	                            std::cout << "ms for process " << running_process.get_id() << " ";
	                            std::cout << pqueue_string(ready_queue) << std::endl;
	                        }
	                        if(t < 1000) {
	                            std::cout << "time " << t << "ms: ";
	                            std::cout << "Process " << running_process.get_id() << " switching out of CPU; ";
	                            std::cout << "will block on I/O until time " << t + running_process.get_io_burst_time() + context_switch;
	                            std::cout << "ms " << pqueue_string(ready_queue) << std::endl;
	                        }   
	                    }
	                    else {
	                        std::cout << "time " << t << "ms: ";
	                        std::cout << "Process " << running_process.get_id() << " terminated ";
	                        std::cout << pqueue_string(ready_queue) << std::endl;
	                    }
                	}
                }
                t_cs--;
                if(t_cs < 0) {
                    t_cs = context_switch;
                    doing_context_switch = false;
                    if(!doing_preemption) {
	                    if(running_process.get_remaining_bursts() == 0) {
	                        erase_process(processes, running_process.get_id());
	                    }
	                    else {
	                        io_queue.push_back(running_process);
	                    }
                	}
                	else {
                		ready_queue.push(running_process);
                	}
                    doing_preemption = false;
                    running_process = Process();
                }
            }
            else {
	            running_process.decrement_cpu_burst();
	            running_process.decrement_tau();
	            running_cpu_bursts++;
            }
        }
        //Check if there is no running process
        else {
            if(!ready_queue.empty() || doing_switch) {
                if(t_cs == context_switch) {
                    doing_switch = true;
                    switch_process = ready_queue.top();
                    ready_queue.pop();
                }
                t_cs--;
                if(t_cs <= 0) {
                    doing_switch = false;
                    running_process = switch_process;
                    t_cs = context_switch;
                    if(t < 1000) {
                        std::cout << "time " << t << "ms: ";
                        std::cout << "Process " <<  running_process.get_id() << " (tau " << running_process.get_tau();
                        std::cout << "ms) started using the CPU for ";
                        if(running_process.get_cpu_burst_time() < running_process.get_original_time()) {
                            std::cout << "remaining " << running_process.get_cpu_burst_time();
                            std::cout << "ms of " << running_process.get_original_time();
                        }
                        else {
                            std::cout << running_process.get_cpu_burst_time();
                        }
                        std::cout << "ms burst " << pqueue_string(ready_queue) << std::endl; 
                    }
                    if(ready_queue.top().get_remaining_tau() < running_process.get_remaining_tau()) {
                    	doing_preemption = true;
                    	preemptions++;
                    	num_context_switches++;
                    	t_cs--;
                    	wait_time--;
                    	if(t < 1000) {
	                    	std::cout << "time " << t << "ms: ";
	                    	std::cout << "Process " <<  ready_queue.top().get_id() << " (tau " << ready_queue.top().get_tau();
	                    	std::cout << "ms) will preempt " << running_process.get_id() << " ";
	                    	std::cout << pqueue_string(ready_queue) << std::endl; 
                    	}
                    }
                    else {
	                    running_process.decrement_cpu_burst();
	                    running_process.decrement_tau();
	                    running_cpu_bursts++;
                	}
                }
            }
        }
        

        //Run the processes doing I/O in alphabetical order
        for(int j = 0; j < int(processes.size()); j++) {
            for(int k = 0; k < int(io_queue.size()); k++)  {
                if(io_queue[k].get_id() == processes[j].get_id()) {
                    if(io_queue[k].get_io_burst_time() == 0) {
                        ready_queue.push(io_queue[k]);
                        //Don't include wait time for a newly introduced process 
                        //in the ready queue
                        wait_time--;

                        if(!running_process.is_empty() && \
                               ready_queue.top().get_remaining_tau() < running_process.get_remaining_tau() &&
                               !doing_context_switch) {
                        	preemptions++;
                        	doing_preemption = true;
                        	t_cs--;
                        	num_context_switches++;
                        	wait_time++;
                        	running_process.increment_cpu_burst();
	            			running_process.increment_tau();
	            			running_cpu_bursts--;
                        }
                        if(t < 1000) {
                            std::cout << "time " << t << "ms: ";
                            std::cout << "Process " << io_queue[k].get_id() << " (tau " << io_queue[k].get_tau();
                            std::cout << "ms) completed I/O; ";
                            if(doing_preemption) {
                            	std::cout << "preempting " << running_process.get_id() << " ";
                            }
                            else
                            	std::cout << "added to ready queue "; 
                            std::cout << pqueue_string(ready_queue) << std::endl;
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
                //Don't include wait time for a newly introduced process 
                //in the ready queue
                wait_time--;
	            if(t < 1000) {
	                std::cout << "time " << t << "ms: ";
	                std::cout << "Process " << processes[i].get_id() << " (tau " << processes[i].get_tau();
	                std::cout << "ms) arrived; ";
	            }
                if(!running_process.is_empty() && \
                   ready_queue.top().get_remaining_tau() < running_process.get_remaining_tau() && \
                   !doing_preemption) {
                   	if(t < 1000)
            			std::cout << "preempting " << running_process.get_id() << " ";
            		doing_preemption = true;
            		preemptions++;
            	}
            	else {
            		if(t < 1000)
            			std::cout << "added to ready queue ";
            	}
            	if(t < 1000)
                	std::cout << pqueue_string(ready_queue) << std::endl;
            }
        }
        if(processes.empty()) {
            std::cout << "time " << t << "ms: ";
            std::cout << "Simulator ended for SRT [Q empty]" << std::endl;
        }
        //Increment the timer
        t++;

        wait_time += ready_queue.size();
    }
    double average_wait_time = double(wait_time)/total_num_bursts;
    int total_turnaround_time = wait_time + num_context_switches * 2 * context_switch + total_cpu_burst_time;
    double avg_turnaround_time = double(total_turnaround_time)/total_num_bursts;
    double cpu_utilization = double(running_cpu_bursts * 100)/(t - 1);
    write_output("SRT", avg_cpu_burst, average_wait_time, avg_turnaround_time, \
                num_context_switches, preemptions, cpu_utilization);
}

