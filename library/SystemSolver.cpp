//
// Created by ariel on 13/11/2019.
//

#include "SystemSolver.h"

SystemSolver::SystemSolver(const DenseMatrix &A) :
    U(DenseMatrix(A.get_n_rows(),A.get_n_cols())), L(DenseMatrix(A.get_n_rows(),A.get_n_cols())){
    LU(A);
}

void SystemSolver::LU(const DenseMatrix &A) {
    const size_t n = A.get_n_cols();

    for (size_t i = 0; i < n; i++) {

        // U
        for (size_t k = i; k < n; k++) {
            double sum = 0;
            for (size_t j = 0; j < i; j++)
                sum += (L(i,j) * U(j,k));

            U(i,k) = A(i,k) - sum;
        }

        // L
        for (size_t k = i; k < n; k++) {
            if (i == k)
                L(i,i) = 1; // Diag 1
            else {
                double sum = 0;
                for (size_t j = 0; j < i; j++)
                    sum += (L(k,j) * U(j,i));

                L(k,i) = (A(k,i) - sum) / U(i,i);
            }
        }
    }

}

vector<double> SystemSolver::LSolve(const vector<double> &b) const {
    vector<double> x(b.size());
    if (b.size() != L.get_n_cols()) {
        std::cerr << "Sizes don't match!" << std::endl;
        return x;
    }
    for (size_t i = 0; i < b.size();i++){
        double sum = 0.0;
        for (size_t k = 0;k<i;k++)
            sum += L(i,k) * x[k];
        x[i] = (b[i] - sum);
    }

    return x;
}

vector<double> SystemSolver::USolve(const vector<double> &b) const {
    vector<double> x(b.size());
    if (b.size() != U.get_n_cols()) {
        std::cerr << "Sizes don't match!" << std::endl;
        return x;
    }
    for (int i = (int) b.size()-1; i >= 0 ;i--){
        double sum = 0.0;
        for (int k = (int) b.size()-1;k>i;k--)
            sum += U(i,k) * x[k];
        x[i] = (b[i] - sum)/U(i,i);
    }

    return x;
}

vector<double> SystemSolver::Solve(const vector<double> &b) const {
    return USolve(LSolve(b));
}

const DenseMatrix &SystemSolver::getL() const {
    return L;
}


const DenseMatrix &SystemSolver::getU() const {
    return U;
}


