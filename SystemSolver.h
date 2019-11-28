//
// Created by ariel on 13/11/2019.
//

#ifndef BLACKSCHOLES_SYSTEMSOLVER_H
#define BLACKSCHOLES_SYSTEMSOLVER_H

#include <iostream>
#include "dense_matrix.hpp"

using std::vector;

class SystemSolver {
private:
    DenseMatrix L;
    DenseMatrix U;
public:
    //! Constructor
    explicit SystemSolver(const DenseMatrix &A);

    //! Utilities
    void LU(const DenseMatrix &A);
    vector<double> LSolve(const vector<double> &b) const;
    vector<double> USolve(const vector<double> &b) const;
    vector<double> Solve(const vector<double> &b) const;

    //! Getter and Setters
    const DenseMatrix &getL() const;
    const DenseMatrix &getU() const;

};

#endif //BLACKSCHOLES_SYSTEMSOLVER_H
