cmake_minimum_required(VERSION 3.16)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project main.cpp FCFS.cpp SJF.cpp SJF.h SRT.cpp SRT.h RR.cpp RR.h Process.h Process.cpp Random.cpp Random.h FCFS.h)