cmake_minimum_required(VERSION 3.16)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project main.cpp FCFS.cpp Algorithm.h SJF.cpp SJF.h SRT.cpp SRT.h RR.cpp RR.h Rand48.h CPU.h Process.h Process.cpp IOSystem.h)