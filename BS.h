//
// Created by ariel on 11/11/2019.
//

#ifndef BLACKSCHOLES_BS_H
#define BLACKSCHOLES_BS_H

#include <cmath>
#include <functional>
#include "RootFind.h"
#include <random>
#include <ctime>

inline double normCDF(double value);
inline int current_time_nanoseconds(){
    struct timespec tm{};
    clock_gettime(CLOCK_REALTIME, &tm);
    return tm.tv_nsec;
}

// black formula
double blkprice(double F0,double B,double K,double T,double sigma, int flag = 1);
double blsprice(double S0, double r, double K, double T, double sigma, double div, int flag = 1);
double impvol(double F0, double B, double K, double T, double price, int flag = 1);
double blkprice_MC(double F0,double B,double K,double T,double sigma,int flag = 1,unsigned N = 1e7);
inline double clip(double num, double min = 0);



#endif //BLACKSCHOLES_BS_H
