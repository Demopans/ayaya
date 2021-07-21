//
// Created by demo on 7/20/2021.
//

#ifndef PROJECT_RAND48_H
#define PROJECT_RAND48_H

#include <cmath>

class SRand48{
public:
    static long i;
    static void init(long n=0){
        i = n & 0xFFFFFFFF;
        i = (i << 16) | 0x330E;
    }
    static double next(){
        i = (0x5DEECE66DL * i + 0xBL) & ((1L << 48) - 1);
        return (double)i;
    }
};


#endif //PROJECT_RAND48_H
