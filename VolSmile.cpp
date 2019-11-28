//
// Created by ariel on 11/11/2019.
//

#include "VolSmile.h"

void VolSmile::newSpot(double K, double price, int flag) {
    bool ins = false;

    double T = yearfrac(settDate,maturity,ACT365);
    double vol = impvol(forward,discount,K,T,price,flag);

    size_t i;

    for (i = 0; i < x.size() && !ins; i++) {
        if (x[i] > K) {
            x.insert(x.begin()+i,K);
            y.insert(y.begin()+i,vol);
            ins = true;
        }
    }
    if(!ins) {
        x.push_back(K);
        y.push_back(vol);
    }
}

void VolSmile::print() const {
    for (size_t i = 0;i < x.size();i++)
        cout << i << ": Strike " << x[i] << "   Volatility " << y[i] << endl;
}

void VolSmile::calibrate() {
    spline();
    coeff = getCoeff();
}
