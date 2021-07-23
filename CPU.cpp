//
// Created by demo on 7/20/2021.
//

#include "CPU.h"

Process *CPU::kickProcess(Process &p) {
    Process *oldP = &this->CurrentProcess;
    this->CurrentProcess = p;// can be nullptr
    return oldP;
}
