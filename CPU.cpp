//
// Created by demo on 7/20/2021.
//

#include "CPU.h"

Process &CPU::kickProcess() {
    Process t = CurrentProcess;
    this->CurrentProcess = Process();
    return t;
}

const Process &CPU::pingProcess() {
    return CurrentProcess;
}

bool CPU::isIdle() {
    return CurrentProcess.get_id()==-1;
}
