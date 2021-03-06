/**
 * Special colorful (if you are using an IDE) Comments for the Betterment of Society and Paul's Ass
 *
 *
 */


#include <iostream>
#include <algorithm>

#include "Algorithm.h"
#include "Process.h"
#include "RR.h"
#include "SJF.h"
#include "SRT.h"
#include "Rand48.h"
#include "Random.h"
#include "FCFS.h"

int main(int argc, char *argv[]) {
    if (argc!=8){// errot handling
        std::string errr = argc < 7 ? "not enough input arguments.\n" : "too many input arguments.\n";
        std::cerr << errr;
        return EXIT_FAILURE;
    }

    /*  first input argument is the number of processes to simulate
        Process IDs are A->Z, so 26 at most */
    std::string ids = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int pCount = std::stoi(argv[1]);
    if (pCount > 26){std::cerr << "too many processes\n.";exit(EXIT_FAILURE);}

    /*  second input argument is the seed for random number generator
        use srand48() before each scheduling algorithm
        use drand48() obtain the next value in range[0.0, 1.0) */
    int seed = std::stoi(argv[2]);
    //srand48(seed);

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
    bool rr_queue_push_end = !(argc >= 9 && std::string(argv[8]) == "BEGINNING" == 0);

    std::vector<Process> processes;
    initialize_processes(pCount,seed,lambda,tail,processes,alpha);

    FCFS(processes, context_switch / 2);
    std::cout << std::endl;
    SJF(processes, context_switch / 2);
    std::cout << std::endl;
    RR(processes, context_switch/2, time_slice);
    std::cout << std::endl;
    return 0;
}