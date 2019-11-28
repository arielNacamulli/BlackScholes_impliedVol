//
// Created by ariel on 12/11/2019.
//

#include "CubicSpline.h"
#include <limits>


void CubicSpline::spline() {
    size_t n = x.size();

    if(n<2){
        std::cerr << "At least 3 points needed" << std::endl;
        return;
    }

    DenseMatrix M ((n-1)*N_PARAMS,(n-1)*N_PARAMS);
    vector<double> b;

    M(0,0) = pow(x[0],3);
    M(0,1) = pow(x[0],2);
    M(0,2) = x[0];
    M(0,3) = 1;
    b.push_back(y[0]);

    //! Null first derivative
    M(1,0) = 3*pow(x[0],2);
    M(1,1) = 2*x[0];
    b.push_back(0.0);

    //! Continuity
    for(size_t i=0;i<n-2;i++) {

        //! First derivative
        M(N_PARAMS * i+2, N_PARAMS*i) = 3*pow(x[i+1], 2);
        M(N_PARAMS * i+2, N_PARAMS*(i+1)) = -3*pow(x[i+1], 2);
        M(N_PARAMS * i+2, N_PARAMS*i+1) = 2*x[i+1];
        M(N_PARAMS * i+2, N_PARAMS*(i+1)+1) = -2*x[i+1];
        M(N_PARAMS * i+2, N_PARAMS*i+2) = 1;
        M(N_PARAMS * i+2, N_PARAMS*(i+1)+2) = -1;

        //! Second derivative
        M(N_PARAMS * i+3, N_PARAMS*i) = 6*x[i+1];
        M(N_PARAMS * i+3, N_PARAMS*(i+1)) = -6*x[i+1];
        M(N_PARAMS * i+3, N_PARAMS*i+1) = 2;
        M(N_PARAMS * i+3, N_PARAMS*(i+1)+1) = -2;

        b.push_back(0.0);
        b.push_back(0.0);

        for (int j = N_PARAMS; j > 0; j--) {
            M(N_PARAMS * i+4, N_PARAMS * (i+1) - j) = pow(x[i+1], j-1);
            M(N_PARAMS * i+5, N_PARAMS * (i+2) - j) = pow(x[i+1], j-1);
        }
        b.push_back(y[i+1]);
        b.push_back(y[i+1]);
    }

    //! Last point

    M(N_PARAMS*(n-2)+2,N_PARAMS*(n-2)) = pow(x[n-1],3);
    M(N_PARAMS*(n-2)+2,N_PARAMS*(n-2)+1) = pow(x[n-1],2);
    M(N_PARAMS*(n-2)+2,N_PARAMS*(n-2)+2) = x[n-1];
    M(N_PARAMS*(n-2)+2,N_PARAMS*(n-2)+3) = 1;
    b.push_back(y[n-1]);

    M(N_PARAMS*(n-2)+3,N_PARAMS*(n-2)) = 3*pow(x[n-1],2);
    M(N_PARAMS*(n-2)+3,N_PARAMS*(n-2)+1) = 2*x[n-1];
    b.push_back(0.0);

    SystemSolver sys(M);
    vector<double> sol = sys.Solve(b);

    coeff=DenseMatrix(n-1,N_PARAMS,sol);
}

vector<double>::const_iterator CubicSpline::interval(double xstar) const {

    for (auto i = x.begin(); i < x.end() - 1; i++)
        if (xstar < *(i+1))
            return i;

    return x.end();
}

double CubicSpline::interpolate(double xstar) const {

    if(coeff.get_n_cols()+coeff.get_n_rows() == 0|| xstar<x.front() || xstar > x.back())
        return std::numeric_limits<double>::quiet_NaN();
    auto it = interval(xstar);
    size_t index = it-x.begin();

    return coeff(index,0)*pow(xstar,3) + coeff(index,1)*pow(xstar,2) +
            coeff(index,2)*xstar + coeff(index,3);
}
