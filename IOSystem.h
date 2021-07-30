//
// Created by demo on 7/29/2021.
//

#ifndef PROJECT_IOSYSTEM_H
#define PROJECT_IOSYSTEM_H

#define op <

bool cc(Process a, Process b) {
    if (a.get_io_burst_time() == b.get_io_burst_time()) {
        a.get_id() op b.get_id();
    }
    return a.get_io_burst_time() op b.get_io_burst_time();
};

class IOSystem{
public:
    std::vector<Process> IOQueue;
    void decrementIOTimer(){
        for (auto &item : IOQueue) {item.decrement_io_burst();}
    }
    void pushIntoIO(Process &p){
        IOQueue.push_back(p);
        std::push_heap(IOQueue.begin(),IOQueue.end(),cc);
    }
    const Process& pingTop(){
        return IOQueue[0];
    }
    void pop(){
        std::pop_heap(IOQueue.begin(),IOQueue.end(),cc);
    }
};

#endif //PROJECT_IOSYSTEM_H
