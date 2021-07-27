//
// Created by demo on 7/20/2021.
//

#ifndef PROJECT_CPU_H
#define PROJECT_CPU_H
#include "Process.h"

class CPU {
public:
    CPU() = default;

    void loadProcess(Process &p){CurrentProcess = p;}
    Process &kickProcess();

    const Process& pingProcess ();
private:
    Process CurrentProcess;
};


#endif //PROJECT_CPU_H
