//
// Created by ariel on 11/11/2019.
//

#ifndef BLACKSCHOLES_ROOTFIND_H
#define BLACKSCHOLES_ROOTFIND_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <functional>

//! From Politecnico di Milano course of Algorthms and Parallel Computing by Danilo Ardagna

//! Type for real numbers
typedef double real;

//! Type for convergence check
enum checkT {
    INCREMENT, //! Check the difference between subsequent iterates
    RESIDUAL,  //! Check the residual
    BOTH       //! Check both conditions
};

real f (real x, const std::function<double(real)>& fun);
real df (real x, const std::function<double(real)>& fun);
bool converged (real increment, real residual,real tol, const checkT& check);
real bisection (real a,  real b,real tol, int maxit,const checkT& check, int& nit, const std::function<double(real)>& fun);
real newton (real xp, real tol, int maxit, const checkT& check, int & nit, const std::function<double(real)>& fun);
real robust(real a, real b, real tol, real cfratio, int maxit, const checkT& check,
            int& nit_coarse, int& nit_fine, const std::function<double(real)>& fun);


#endif //BLACKSCHOLES_ROOTFIND_H
