//
// Created by ariel on 12/11/2019.
//

#ifndef BLACKSCHOLES_CUBICSPLINE_H
#define BLACKSCHOLES_CUBICSPLINE_H

#include <utility>
#include <vector>
#include "SystemSolver.h"
#include <cmath>

#define N_PARAMS 4

using std::vector;

class CubicSpline {
protected:
    DenseMatrix coeff; // a*x^3 + b*x^2 + c*x + d
    vector<double> x;
    vector<double> y;
public:
    CubicSpline(vector<double> _x, vector<double> _y): x(std::move(_x)),y(std::move(_y)),coeff(0,0){}
    void spline();
    DenseMatrix getCoeff(){return coeff;}
    double interpolate(double xstar) const;
    vector<double>::const_iterator interval(double xstar) const;

};


#endif //BLACKSCHOLES_CUBICSPLINE_H
