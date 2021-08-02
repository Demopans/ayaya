//
// Created by demo on 7/19/2021.
//

#include "SRT.h"
#define op >

bool SRT::compare(const Process& a, const Process& b) {
    if (a.get_cpu_burst_time() == b.get_cpu_burst_time()){
        return a.get_arrival_time() op b.get_arrival_time();
    }
    return a.get_cpu_burst_time() op b.get_cpu_burst_time();
}

