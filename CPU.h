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
    Process kickProcess(){
        Process t = CurrentProcess;
        this->CurrentProcess = Process();
        return t;
    }

    const Process& pingProcess (){
        return CurrentProcess;
    }

    bool isIdle(){
        return CurrentProcess.get_id()==-1;
    }

    void subCPUTime(){
        CurrentProcess.decrement_cpu_burst();
    }
private:
    Process CurrentProcess;
};


#endif //PROJECT_CPU_H
