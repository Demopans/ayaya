//
// Created by demo on 7/19/2021.
//

#ifndef PROJECT_SJF_H
#define PROJECT_SJF_H

#include <algorithm>
#include <queue>
#include "Algorithm.h"
#include "Event.h"

bool eventComparator(Event a, Event b);

class SJF : private Algorithm{
    std::priority_queue<Event> queue;
};


#endif //PROJECT_SJF_H
