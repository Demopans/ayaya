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

public:
    void process(const std::vector<Process>& pids, double lambda, double alpha);
};


#endif //PROJECT_SRT_H
