//
// Created by Colin on 7/20/2021.
//

#include "Process.h"

Process::Process(char id, int cpu_burst, int io_burst, int arrival, int num_bursts) {
	this->id = id;
	this->num_cpu_bursts  = num_bursts;
	this->cpu_burst_time = cpu_burst;
	this->io_burst_time = io_burst;
	this->arrival_time = arrival;
}