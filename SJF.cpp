//
// Created by demo on 7/19/2021.
//

#include "SJF.h"
#define op >

bool eventComparator(Process a, Process b) {
    if (a.get_cup_burst_time() == b.get_cup_burst_time()){
        return a.get_arrival_time() op b.get_arrival_time();
    }
    return a.get_cup_burst_time() op b.get_cup_burst_time();
}

void SJF::oneRound() {

}

void SJF::pushToQueue(Process &p) {
    this->queue.push(p);
}
