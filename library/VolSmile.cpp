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

void VolSmile::read(const string &file) {

    double tempStrike,tempPrice;
    int tempFlag;
    std::ifstream ist{file};
    if(!ist)
        cout << "Can't open the file!" << endl;
    while(ist >> tempStrike >> tempPrice >> tempFlag)
        newSpot(tempStrike,tempPrice,tempFlag);
}

void VolSmile::write(const string &file, int len) const {
    std::ofstream ost{file};
    vector<double> KVec = linspace(x.front(),x.back(),len);
    vector<double> curve(len);

    for(size_t i = 0; i < len; i++)
        curve[i] = interpolate(KVec[i]);

    for(size_t i = 0; i < len; i++)
        ost << KVec[i] << ' ' << curve[i] << endl;
}
