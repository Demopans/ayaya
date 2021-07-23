//
// Created by demo on 7/20/2021.
//

#ifndef PROJECT_CPU_H
#define PROJECT_CPU_H
#include "Process.h"

class CPU {
public:
    void loadProcess(Process &p){CurrentProcess = p;}
    void runProcess();
    Process* kickProcess(Process &p);
private:
    Process CurrentProcess;
};


#endif //PROJECT_CPU_H
