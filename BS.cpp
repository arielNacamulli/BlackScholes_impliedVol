//
// Created by ariel on 11/11/2019.
//

#include "BS.h"

double normCDF(double value)
{
    return 0.5 * erfc(-value * M_SQRT1_2);
}

double blkprice(double F0, double B, double K, double T, double sigma, int flag) {
/*! F0 Forward price
 * B Discount
 * K Strike
 * T Maturity
 * sigma Volatility
 * flag -1 put, 1 call
 */

    double d1 = log(F0/K)/(sigma*sqrt(T)) + 0.5*sigma*sqrt(T);
    double d2 = d1 - sigma*sqrt(T);
    double price = flag * B *(F0 * normCDF(flag*d1) - K * normCDF(flag*d2));

    return price;
}

double blsprice(double S0, double r, double K, double T, double sigma, double div = 0, int flag){
/*! S0 Strike price
 * r Rate
 * K Strike
 * T Maturity
 * sigma Volatility
 * div Dividend yield
 * flag -1 put, 1 call
 */

    return blkprice(S0 * exp(-(r-div)*T),exp(-r*T),K,T,sigma,flag);
}

double impvol(double F0, double B, double K, double T, double price, int flag){
/*! F0 Forward price
 * B Discount
 * K Strike
 * T Maturity
 * price Price
 * flag -1 put, 1 call
 */

    std::function<double (double)> fun = [F0,B,K,T,flag, price](double sigma) {
        return blkprice(F0,B,K,T,sigma,flag) - price;
    };
    int nit_bis;
    int nit_newt;
    return robust(0.,1.,1e-8,1e4,100,BOTH,nit_bis,nit_newt,fun);
}

double blkprice_MC(double F0, double B, double K, double T, double sigma, int flag, unsigned int N) {
    std::mt19937 rng(current_time_nanoseconds());
    std::normal_distribution<double> distribution(0,1.0);
    double payoff = 0;
    for (size_t i = 0; i<N; i++){
        double z = distribution(rng);
        payoff += clip((F0*exp(-sigma*sigma*0.5*T + sigma*sqrt(T)*z)-K)*flag);
    }

    return payoff*B/N;
}

double clip(double num, double min) {
    return std::max(num,min);
}
