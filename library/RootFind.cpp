//
// Created by ariel on 11/11/2019.
//

#include "RootFind.h"

// Modified by Ariel Nacamulli 11/11/2019

#include "RootFind.h"
#define epsilon 1e-6

//! Function f(x)
real f (real x, const std::function<double(real)>& fun) {
    return fun(x);
}

//! First derivative of function f(x)
real df (real x, const std::function<double(real)>& fun) {
    real delta = x*epsilon;

    return (f(x+delta, fun) - f(x, fun))/delta;
}

bool converged (real increment, real residual,
                real tol, const checkT& check){
    /*
      Compares a parameter value against desired tolerance.
      The parameter is chosen upon the value of check.
    */
    switch(check){
        case INCREMENT:
            return (increment < tol);
        case RESIDUAL:
            return (residual < tol);
        case BOTH:
            return ((increment < tol)&&(residual < tol));
        default:
            return false;
    }
}

// BISECTION METHOD
real bisection (real a,  real b,
                real tol, int maxit,
                const checkT& check, int& nit, const std::function<double(real)>& fun)
{
    real u = f(a, fun);  // Evaluate f on boundary a
    real l = b - a; // Interval length
    real r;         // Residual
    real c = a+l;   // Middle point

    nit = 0;
    r = f(c, fun);

    if (u*f(b, fun)>=0.0) {
        std::cerr<<"Error Function has same sign at both endpoints"<<std::endl;
        return - std::numeric_limits<double>::infinity();
    }

    while ( !(converged(fabs(l), fabs(r), tol, check))
            && (nit <= maxit) ) {
        /*
          If f(c)f(a) < 0 then the new "right" boundary is c;
          otherwise move the "left" boundary

          The expression
             test ? stat1 : stat2
          means
             if(test)
                stat1
             else
                stat2
        */
        (u*r < 0.) ? (b = c) : (a = c, u = r);
        l *= 0.5;
        c = a + l;
        r = f(c, fun);
        ++nit;
    }
    return c;
}


// NEWTON METHOD
real newton (real xp, real tol, int maxit,
             const checkT& check, int & nit, const std::function<double(real)>& fun)
{
    real v = f(xp, fun);
    real xnew;

    nit = 0;
    bool conv=false;

    for(int k = 1; k <= maxit && !conv; ++k,++nit) {
        double derv = df(xp, fun);
        if(!derv) {
            std::cerr << "ERROR: Division by 0 occurred in Newton algorithm"
                      << std::endl;
            exit(1);
        }

        xnew = xp - v / derv;
        v = f(xnew, fun);
        conv=converged(fabs(xnew - xp), fabs(v),tol,check);
        if(!conv)
            xp = xnew;
    }
    return xnew;


}


// ROBUST METHOD
real robust(real a, real b,
            real tol, real cfratio,
            int maxit, const checkT& check,
            int& nit_coarse, int& nit_fine, const std::function<double(real)>& fun) {
    // Call bisection method (with a greater desired tolerance)
    real tol_bis = cfratio * tol;
    real x_bis = bisection(a, b, tol_bis, maxit, check, nit_coarse, fun);

    /*
      Call a Newton algorithm which uses as an initial value
      the solution given by bisection method
    */

    return newton(x_bis, tol, maxit, check, nit_fine, fun);
}
