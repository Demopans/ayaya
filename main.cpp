#include "Random.h"
#include "Process.h"
#include "FCFS.h"
#include "SJF.h"
#include "SRT.h"
#include "RR.h"

int main(int argc, char *argv[]) {
    if (argc!=8){// errot handling
        std::string errr = argc < 7 ? "not enough input arguments.\n" : "too many input arguments.\n";
        std::cerr << errr;
        return EXIT_FAILURE;
    }
    int pCount = std::stoi(argv[1]);
    if (pCount > 26){std::cerr << "too many processes\n.";exit(EXIT_FAILURE);}

    /*  second input argument is the seed for random number generator
        use srand48() before each scheduling algorithm
        use drand48() obtain the next value in range[0.0, 1.0) */
    int seed = std::stoi(argv[2]);

    /*  third input argument is the lambda for calculating an exponential distribution of interarrival times
        fourth input argument is the upper bound for exponential distribution numbers
        use in the ceiling function */
    double lambda = std::stof(argv[3]);
    double tail = std::stof(argv[4]);

    /*  fifth input argument is t_cs in milliseconds to perform a context switch
        the 1st half of t_cs is the time to remove given process from CPU
        the 2nd half of t_cs is the time to bring the next process to CPU
        positive even integer */
    int context_switch = std::stoi(argv[5]);
    if (context_switch <= 0 || context_switch % 2 == 1){
        std::cerr << "invalid context_switch, need a positive even integer\n.";return EXIT_FAILURE;
    }

    /*  sixth input agurment is the constant alpha for exponential averaging
        use ceiling function when calculating τ */
    double alpha = std::stod(argv[6]);

    /*  seventh input argument is the t_slice for time slice in RR in milliseconds
        eighth input argument is rr_add the flag for whether processes are added to the end or beginning of the ready queue */
    int time_slice = std::stoi(argv[7]);
    std::vector<Process> init_processes;
    initialize_processes(pCount, seed, lambda, tail, init_processes, alpha);
    for(int m = 0; m < pCount; m++) {
        std::cout << "Process " << init_processes[m].get_id() << " (arrival time ";
        std::cout << init_processes[m].get_arrival_time() << " ms) ";
        std::cout << init_processes[m].get_num_cpu_bursts();
        if(init_processes[m].get_num_cpu_bursts() != 1)
            std::cout << " CPU bursts (tau ";
        else
            std::cout << " CPU burst (tau ";
        std::cout << init_processes[m].get_tau() << "ms)" << std::endl;
    }
    std::cout << std::endl;
    FCFS(pCount, seed, context_switch/2, lambda, tail);
    std::cout << std::endl;
    SJF(pCount, seed, context_switch/2, lambda, tail, alpha);
    std::cout << std::endl;
    SRT(pCount, seed, context_switch/2, lambda, tail, alpha);
    std::cout << std::endl;
    RR(pCount, seed, context_switch/2, lambda, tail, time_slice);
    return 0;
}