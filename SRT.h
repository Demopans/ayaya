//
// Created by demo on 7/19/2021.
//

#ifndef PROJECT_SRT_H
#define PROJECT_SRT_H

#include <algorithm>
#include <queue>
#include "Algorithm.h"
#include "Process.h"





class SRT : private Algorithm{
private:
    static bool compare(const Process& a, const Process& b);
    struct com{
        bool operator()(const Process& a, const Process& b){return compare(a,b);}
    };
    std::priority_queue<Process,std::vector<Process>,com> queue;
public:
    void process();
};


#endif //PROJECT_SRT_H
